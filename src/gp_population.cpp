#include "gp_population.h"

/*
   ============
   construction
   ============
*/

synthax::gp_population::gp_population(aux::logger* logger, gp_population_params* params, random* rng, std::vector<node*>* primitives) :
    logger(logger),
    params(params), rng(rng), availablePrimitives(primitives),
    allNetworks(), unevaluated(), evaluated(), currentGeneration(),
    rawFitnesses(), normalizedFitnesses(), rank()
{
    // init public evolution sate
    currentGenerationNumber = 0;
    generationChamp = NULL;
    champ = NULL;

    // init private evolution state
    populationSize = params->population_size;
    nextNetworkid = 0;
    lowerFitnessIsBetter = params->lower_fitness_is_better;
    overallBestFitness = lowerFitnessIsBetter ? std::numeric_limits<double>::max() : 0;
    currentGenerationAlive = false;

    // categorize primitives
    availableFunctions = new std::vector<node*>();
    availableTerminals = new std::vector<node*>();
    for (unsigned i = 0; i < availablePrimitives->size(); i++) {
		std::cerr << availablePrimitives->at(i)->to_string(4);
		std::string prim_string = availablePrimitives->at(i)->to_string(4);
        if (availablePrimitives->at(i)->arity == 0) {
            availableTerminals->push_back(availablePrimitives->at(i));
        }
        else {
            availableFunctions->push_back(availablePrimitives->at(i));
        }
    }
    assert(availableFunctions->size() > 0 && availableTerminals->size() > 0);

    // init generation containers
    clearGenerationState();

    // create initial population
    initPopulation();

    // declare the start of generation 0
    printGenerationDelim();
}

synthax::gp_population::~gp_population() {
    clearGenerationState();
    for (unsigned i = 0; i < availablePrimitives->size(); i++) {
        delete availablePrimitives->at(i);
    }
	// TODO: maybe delete this elsewhere and pass by reference or something
    delete availablePrimitives;
    delete availableFunctions;
    delete availableTerminals;
    delete generationChamp;
    delete champ;
}

synthax::node* synthax::gp_population::fullRecursive(unsigned cd, unsigned d) {
    if (cd == d) {
        node* term = availableTerminals->at(rng->drandom(availableTerminals->size()))->get_copy();
        return term;
    }
    else {
        node* ret = availableFunctions->at(rng->drandom(availableFunctions->size()))->get_copy();
        for (unsigned i = 0; i < ret->arity; i++) {
            ret->descendants[i] = fullRecursive(cd + 1, d);
        }
        return ret;
    }
}

synthax::algorithm* synthax::gp_population::full(unsigned d) {
    return new algorithm(fullRecursive(0, d), "full");
}

synthax::node* synthax::gp_population::growRecursive(unsigned cd, unsigned m) {
    if (cd == m) {
        node* term = availableTerminals->at(rng->drandom(availableTerminals->size()))->get_copy();
        return term;
    }
    else {
        node* ret;
        if (cd == 0) {
            ret = availableFunctions->at(rng->drandom(availableFunctions->size()))->get_copy();
        }
        else {
            ret = availablePrimitives->at(rng->drandom(availablePrimitives->size()))->get_copy();
        }
        if (ret->arity == 0) {
            return ret;
        }
        for (unsigned i = 0; i < ret->arity; i++) {
            ret->descendants[i] = growRecursive(cd + 1, m);
        }
        return ret;
    }
}

synthax::algorithm* synthax::gp_population::grow(unsigned m) {
    return new algorithm(growRecursive(0, m), "grow");
}

void synthax::gp_population::initPopulation() {
    logger->log << "Initializing population of size " << populationSize << std::flush;

	// if maxInitialHeight is 0 we just want a single terminal
    algorithm* newnet;
    unsigned maxInitialHeight = params->max_initial_height;
	if (maxInitialHeight == 0) {
		for (unsigned i = 0; i < populationSize; i++) {
			newnet = full(0);
			addNetworkToPopulation(newnet);
		}
		return;
	}

    // implementation of ramped half and half
    unsigned numPerPart = maxInitialHeight <= 1 ? 0 : populationSize / (maxInitialHeight - 1);
    unsigned numFullPerPart = numPerPart / 2;
    unsigned numGrowPerPart = numFullPerPart + (numPerPart % 2);
    unsigned additionalLargest = maxInitialHeight <= 1 ? populationSize : populationSize % (maxInitialHeight - 1);
    unsigned additionalFull = additionalLargest / 2;
    unsigned additionalGrow = additionalFull + (additionalLargest % 2);

    // TODO: test for equality before adding to population
    for (unsigned i = 0; i < maxInitialHeight - 1; i++) {
        for (unsigned j = 0; j < numFullPerPart; j++) {
            newnet = full(i + 2);
            if (params->erc)
                newnet->ephemeral_random(rng);
            addNetworkToPopulation(newnet);
        }
        for (unsigned j = 0; j < numGrowPerPart; j++) {
            newnet = grow(i + 2);
            if (params->erc)
                newnet->ephemeral_random(rng);
            addNetworkToPopulation(newnet);
        }
    }
    for (unsigned j = 0; j < additionalFull; j++) {
        newnet = full(maxInitialHeight);
        if (params->erc)
            newnet->ephemeral_random(rng);
        addNetworkToPopulation(newnet);
    }
    for (unsigned j = 0; j < additionalGrow; j++) {
        newnet = grow(maxInitialHeight);
        if (params->erc)
            newnet->ephemeral_random(rng);
        addNetworkToPopulation(newnet);
    }
    assert(unevaluated.size() == populationSize);

    currentGenerationAlive = true;
}

/*
   =================
   EVOLUTION CONTROL
   =================
*/

synthax::algorithm* synthax::gp_population::getIndividual() {
    // if no more networks remain advance population
    if (unevaluated.empty()) {
        nextGeneration();
    }

    // logic to deal with reproduced algorithms for efficiency
    algorithm* ret = *(unevaluated.begin());
    logger->verbose << "Testing algorithm " << ret->id << " made by " << ret->origin << " with height " << ret->height << " and structure " << logger->net_to_string_print(ret) << std::flush;
    return ret;
}

void synthax::gp_population::getIndividuals(std::vector<algorithm*>& networks) {
    // if no more networks remain advance population
    if (unevaluated.empty()) {
        nextGeneration();
    }

	// if too many networks were asked for print and return
    if (unevaluated.size() < networks.size()) {
        logger->error << "Requested multiple individuals out of population that did not have enough remaining" << std::flush;
        return;
    }

	// fill 'er up! (you should assignFitness on all of these before asking for another block
	// otherwise you will probably get the same networks)
	unsigned i = 0;
	for (std::set<algorithm*>::iterator iter = unevaluated.begin(); i < networks.size(); i++, iter++) {
		networks[i] = *(iter);
	}

	// sort synth voices by id
	std::sort(networks.begin(), networks.end(), compare_algorithms_by_id);
}

synthax::algorithm* synthax::gp_population::growNewIndividual(unsigned maxHeight) {
	algorithm* nu = grow(maxHeight);
	if (params->erc)
		nu->ephemeral_random(rng);

	return nu;
}

bool synthax::gp_population::replaceIndividual(algorithm* old, algorithm* nu) {
	// check if old is already evaluated
	if (evaluated.find(old) != evaluated.end()) {
        logger->error << "Tried replacing population individual that had already been evaluated" << std::flush;
		return false;
	}

	// check if old is still in population
	unsigned oldGenerationid = old->id % populationSize;
	if (currentGeneration[oldGenerationid] != old) {
		logger->error << "Tried replacing individual that is not in the current generation" << std::flush;
		return false;
	}

	// check to make sure nu is the right height
	nu->trace();
	if (nu->height > params->max_height) {
		logger->error << "Tried replacing individual that is too tall for the population" << std::flush;
		// TODO: change this
		// return false;
	}

	// otherwise lets go ahead and insert it into our population
	nu->id = old->id;

	// replace the old network in the current generation
	currentGeneration[oldGenerationid] = nu;

	// replace the old in evaluated/unevaluated
	unevaluated.erase(old);
	evaluated.erase(old);
    if (nu->fitness != -1) {
        logger->log << "Replacement individual " << nu->id << " made by " << nu->origin << " with height " << nu->height << " and structure " << logger->net_to_string_print(nu) << " was already evaluated and replaced algorithm " << old->id << " ." << std::flush;
        
        assignFitness(nu, nu->fitness);
    }
    else {
        unevaluated.insert(nu);
    }

	// replace the old network in the string backups
    if (params->backup_all_networks) {
		allNetworks[oldGenerationid] = nu->to_string(params->backup_precision);
	}

	// delete the old
	delete old;

	// replacement successful
	return true;
}

int synthax::gp_population::assignFitness(algorithm* net, double fitness) {
    // assign network fitness and move it to evaluated
    net->fitness = fitness;
    unevaluated.erase(net);
    evaluated.insert(net);
    rawFitnesses[net->id % populationSize] = fitness;

    // print if verbose
    logger->verbose << "Algorithm " << net->id << " was assigned fitness " << fitness << std::flush;

    // calculate num remaining and print summary if generation is done
    int numStillNeedingEvaluation = populationSize - evaluated.size();
    if (numStillNeedingEvaluation == 0) {
        endGeneration();
        printGenerationSummary();
    }
    return numStillNeedingEvaluation;
}

int synthax::gp_population::prevGeneration() {
	// check to see we're not at generation 1
    if (currentGenerationNumber == 0) {
        logger->error << "Attempted to revert to a previous generation during generation 0" << std::flush;
        return currentGenerationNumber;
    }

	// check to see if we are backing up
	if (!params->backup_all_networks) {
        logger->error << "Attempted to revert to a previous generation but no networks backed up" << std::flush;
        return currentGenerationNumber;
	}

	// clear out current generation state
	clearGenerationState();

	// recreate the old networks
	std::vector<algorithm*> lastGeneration(0);
	for (unsigned i = 0; i < populationSize; i++) {
		// sort by id in fillFromGeneration()
		std::string oldnetstring = allNetworks[((currentGenerationNumber - 1) * populationSize) + i];
		std::string error_string = "";
		node* oldnode = parser::create_node(oldnetstring, &error_string);
		algorithm* oldnetwork = new algorithm(oldnode, "restored_from_last_gen");
		lastGeneration.push_back(oldnetwork);
	}
	
	// delete old strings
	// we have to remove 2 * popsize because we're supposed to be at the end state of 2 gens ago
	for (unsigned i = 0; i < populationSize * 2; i++) {
		allNetworks.pop_back();
	}
	//appendToTextFile("./debug.txt", "ALL NETWORKS AFTER DELETE: " + String(allNetworks.size()) + "\n");

	// add old networks back to population
	nextNetworkid -=  2 * populationSize;
	for (unsigned i = 0; i < populationSize; i++) {
		addNetworkToPopulation(lastGeneration[i]);
	}
	//appendToTextFile("./debug.txt", "ALL NETWORKS AFTER ADD: " + String(allNetworks.size()) + "\n");

	// decrement generation number and return it
    currentGenerationNumber--;
    return currentGenerationNumber;
}

void synthax::gp_population::printGenerationDelim() {
    logger->log << "------------------------- START OF GENERATION " << currentGenerationNumber << " -------------------------" << std::flush;
}

void synthax::gp_population::endGeneration() {
    assert(currentGenerationAlive);

    // parse assigned fitnesses
    unsigned generationBestNetworkid = 0;
    double generationCumulativeFitness = 0;
    for (std::set<algorithm*>::iterator i = evaluated.begin(); i != evaluated.end(); i++) {
        // find fitness
        algorithm* evaluatedNet = (*i);
        unsigned generationid = evaluatedNet->id % populationSize;
        double fitness = rawFitnesses[generationid];

        // report if fitness negative
        if (fitness < 0) {
            logger->error << "Negative fitness value detected when summarizing generation" << std::flush;
        }

        // determine if we have a new generation champion
        bool newGenChamp = lowerFitnessIsBetter ? fitness < generationBestFitness : fitness > generationBestFitness;
        if (newGenChamp) {
            generationBestNetworkid = generationid;
            generationBestFitness = fitness;
        }

        // update cumulative fitness
        generationCumulativeFitness += fitness;
    }

    // calculate average fitness
    generationAverageFitness = generationCumulativeFitness / evaluated.size();

    // update generation champ
    algorithm* best = currentGeneration[generationBestNetworkid];
    delete generationChamp;
    generationChamp = best->get_copy(best->origin);
    generationChamp->id = best->id;
    generationChamp->fitness = generationBestFitness;
    generationChamp->trace();

    // update overall champ
    bool newChamp = lowerFitnessIsBetter ? generationBestFitness < overallBestFitness : generationBestFitness > overallBestFitness;
	if (newChamp) {
		delete champ;
		champ = best->get_copy(best->origin);
		champ->id = best->id;
		champ->fitness = generationBestFitness;
		champ->trace();
        overallBestFitness = generationBestFitness;
	}
    
    currentGenerationAlive = false;
}

void synthax::gp_population::printGenerationSummary() {
    // print generation summary
    logger->log << "Generation " << currentGenerationNumber << " had average fitness " << generationAverageFitness << " and best fitness " << generationBestFitness << " attained by algorithm " << generationChamp->id << " made by " << generationChamp->origin << " with height " << generationChamp->height << " and structure " << logger->net_to_string_print(generationChamp) << std::flush;
}

void synthax::gp_population::printEvolutionSummary() {
    float numEvaluatedGenerations = (float) currentGenerationNumber + (evaluated.size() / populationSize);

    logger->log << "-------------------------------- SUMMARY --------------------------------" << std::flush;
    logger->log << "Evolution ran for " << numEvaluatedGenerations << " generations" << std::flush;
    if (champ != NULL) {
        logger->log << "The best synthesis algorithm found was number " << champ->id << " made by " << champ->origin << " with height " << champ->height << ", fitness " << champ->fitness << " and structure " << logger->net_to_string_print(champ) << std::flush;
    }
}

void synthax::gp_population::getCurrentGeneration(std::vector<algorithm*>& networks) {
    for (int i = 0; i < populationSize; i++) {
        networks.push_back(currentGeneration[i]);
    }
}

int synthax::gp_population::nextGeneration() {
    assert(!currentGenerationAlive);
    assert(evaluated.size() == rawFitnesses.size());
    assert(evaluated.size() == populationSize);
    assert(unevaluated.size() == 0);

    // CREATE TEMP CONTAINER FOR NEXT GENERATION
    std::vector<algorithm*>* nextGeneration = new std::vector<algorithm*>();

    // CALCULATE NUMBER OF INDIVidUALS BY EACH MUTATION TYPE
    double proportionSum = 0;
    proportionSum += params->nm_proportion + params->mu_proportion + params->x_proportion + params->re_proportion + params->new_proportion;

    unsigned numToNumericMutate = (unsigned) ((params->nm_proportion) * populationSize);
    unsigned numToMutate = (unsigned) ((params->mu_proportion/proportionSum) * populationSize);
    unsigned numToCrossover = (unsigned) ((params->x_proportion/proportionSum) * populationSize);
    unsigned numToReproduce = (unsigned) ((params->re_proportion/proportionSum) * populationSize);
    unsigned numToCreate = (unsigned) ((params->new_proportion/proportionSum) * populationSize);

    assert(numToNumericMutate + numToMutate + numToCrossover + numToReproduce + numToCreate <= populationSize);
    numToCrossover += populationSize - (numToNumericMutate + numToMutate + numToCrossover + numToReproduce + numToCreate);

    //std::cout << populationSize << ", " << numToNumericMutate << ", " << numToMutate << ", " << numToCrossover << ", " << numToReproduce << std::endl;

    // NUMERIC MUTATION
    unsigned numForPossibleNumericMutation = params->nm_selection_percentile * populationSize;
    for (unsigned i = 0; i < numToNumericMutate; i++) {
        algorithm* selected = selectFromEvaluated(params->nm_selection_type, numForPossibleNumericMutation);
        algorithm* one = selected->get_copy("numeric mutation");
        one->trace();
        numericallyMutate(one);
        nextGeneration->push_back(one);
        //selected->fitness = newfitness;
        //rawFitnesses[selected->id % populationSize] = newfitness;
    }

    // MUTATION
    unsigned numForPossibleMutation = params->mu_selection_percentile * populationSize;
    for (unsigned i = 0; i < numToMutate; i++) {
        algorithm* selected = selectFromEvaluated(params->mu_selection_type, numForPossibleMutation);
        algorithm* one = selected->get_copy("mutation");
        one->trace();
        mutate(params->mu_type, one);
        nextGeneration->push_back(one);
        //selected->fitness = newfitness;
    }

    // CROSSOVER
    unsigned numForPossibleCrossover = params->x_selection_percentile * populationSize;
    for (unsigned i = 0; i < numToCrossover;) {
        algorithm* dad = selectFromEvaluated(params->x_selection_type, numForPossibleCrossover);
        algorithm* mom = selectFromEvaluated(params->x_selection_type, numForPossibleCrossover);
        algorithm* one = dad->get_copy("crossover");
        int oneid = dad->id;
        double oneFitness = one->fitness;
        one->trace();
        algorithm* two = mom->get_copy("crossover");
        int twoid = mom->id;
        double twoFitness = two->fitness;
        two->trace();

        algorithm* offspring = crossover(params->x_type, one, two);

        // standard GP with two offspring
        if (offspring == NULL) {
            one->trace();
			assert(one->height >= 0);
            if ((unsigned) one->height > params->max_height) {
                delete one;
                one = dad->get_copy("reproduction during crossover");
                one->id = oneid;
                one->fitness = oneFitness;
            }
            nextGeneration->push_back(one);
            i++;
            if (i < numToCrossover) {
                two->trace();
				assert(two->height >= 0);
                if ((unsigned) two->height > params->max_height) {
                    delete two;
                    two = mom->get_copy("reproduction during crossover");
                    two->id = twoid;
                    two->fitness = twoFitness;
                }
                nextGeneration->push_back(two);
                i++;
            }
            else {
                delete two;
            }
        }
        // some other type with one offspring
        else {
            nextGeneration->push_back(offspring);
        }
    }

    // REPRODUCTION
    unsigned numForPossibleReproduction = params->re_selection_type;
    for (unsigned i = 0; i < numToReproduce; i++) {
        algorithm* selected = selectFromEvaluated(params->re_selection_type, numForPossibleReproduction);
        int oldid = selected->id;
        double oldFitness = selected->fitness;
        algorithm* one = selected->get_copy("reproduction");
        one->id = oldid;
        one->fitness = oldFitness;
        nextGeneration->push_back(one);
    }

    // CREATE
    for (unsigned i = 0; i < numToCreate; i++) {
        algorithm* one = newIndividual(params->new_type);
        one->trace();
        nextGeneration->push_back(one);
    }


    // DELETE STATE FROM LAST GENERATIOn
    clearGenerationState();

    // INCREMENT THE GENERATION COUNT
    currentGenerationNumber++;

    // PRINT START OF GENERATION DELIMITER
    printGenerationDelim();

    // POPULATE STATE WITH NEXT GENERATION
    assert(nextGeneration->size() == populationSize);
    for (unsigned i = 0; i < populationSize; i++) {
        addNetworkToPopulation(nextGeneration->at(i));
    }
    delete nextGeneration;

    currentGenerationAlive = true;

    return currentGenerationNumber;
}

void synthax::gp_population::calculateGenerationRanks() {
    for (unsigned i = 0; i < populationSize; i++) {
        rank[i] = currentGeneration[i];
    }
    if (lowerFitnessIsBetter)
        std::sort(rank.begin(), rank.end(), compareFitnessesLower);
    else
        std::sort(rank.begin(), rank.end(), compareFitnessesHigher);
}

void synthax::gp_population::calculateGenerationNormalizedFitnesses() {
    // STANDARDIZE FITNESS
    std::vector<double>* standardizedFitnesses;
    if (lowerFitnessIsBetter) {
        standardizedFitnesses = &rawFitnesses;
    }
    else {
        standardizedFitnesses = new std::vector<double>();
        for (unsigned i = 0; i < rawFitnesses.size(); i++) {
            standardizedFitnesses->push_back(params->best_possible_fitness - rawFitnesses[i]);
        }
    }

    // ADJUST FITNESS
    std::vector<double>* adjustedFitnesses = new std::vector<double>();
    double sum = 0;
    double si = 0;
    for (unsigned i = 0; i < standardizedFitnesses->size(); i++) {
        si = 1/(1 + standardizedFitnesses->at(i));
        sum += si;
        adjustedFitnesses->push_back(si);
    }

    // NORMALIZE FITNESS
    for (unsigned i = 0; i < adjustedFitnesses->size(); i++) {
        normalizedFitnesses[i] = (adjustedFitnesses->at(i)/sum);
    }

    // DELETE INTERMEDIATE DATA
    if (!lowerFitnessIsBetter) {
        delete standardizedFitnesses;
    }
    delete adjustedFitnesses;
}

/*
   =======
   helpers
   =======
*/

void synthax::gp_population::addNetworkToPopulation(algorithm* net) {
    int oldid = -1;
    if (net->fitness != -1) {
        oldid = net->id;
    }
    net->id = nextNetworkid++;
    net->trace();
    assert(net->height >= 0 && (unsigned) net->height <= params->max_height);
    if (params->backup_all_networks)
      allNetworks.push_back(net->to_string(params->backup_precision));
    currentGeneration.insert(std::make_pair(net->id % populationSize, net));
    if (net->fitness != -1 && !params->re_reevaluate) {
		// TODO: reorder sanity of this message
        logger->verbose << "Testing algorithm " << net->id << " made by " << net->origin << " with height " << net->height << " and structure " << logger->net_to_string_print(net) << " which was algorithm " << oldid << " from the previous generation." << std::flush;
        assignFitness(net, net->fitness);
    }
    else {
        unevaluated.insert(net);
    }
}

void synthax::gp_population::clearGenerationState() {
    // delete all networks from last generation
    for (std::set<algorithm*>::iterator i = unevaluated.begin(); i != unevaluated.end(); i++) {
        delete (*i);
    }
    for (std::set<algorithm*>::iterator i = evaluated.begin(); i != evaluated.end(); i++) {
        delete (*i);
    }
    evaluated.clear();
    unevaluated.clear();
    currentGeneration.clear();
    generationBestFitness = lowerFitnessIsBetter ? std::numeric_limits<double>::max() : 0;
    generationAverageFitness = lowerFitnessIsBetter ? std::numeric_limits<double>::max() : 0;

    // clear out selection containers
    rawFitnesses.clear();
    rawFitnesses.resize(populationSize, -1.0);
    normalizedFitnesses.clear();
    normalizedFitnesses.resize(populationSize, -1.0);
    rank.clear();
    rank.resize(populationSize, NULL);
}

synthax::algorithm* synthax::gp_population::selectFromEvaluated(unsigned selectionType, unsigned parameter) {
    //http://en.wikipedia.org/wiki/Selection_%28genetic_algorithm%29
    assert(rawFitnesses.size() == populationSize && normalizedFitnesses.size() == populationSize);
    if (selectionType == 0 && normalizedFitnesses[0] == -1) {
        calculateGenerationNormalizedFitnesses();
    }
    else if (selectionType == 1 && rank[0] == NULL) {
        calculateGenerationRanks();
    }

    if (selectionType == 0) {
        // fitness proportionate selection
        return currentGeneration[rng->sampleFromDistribution(&normalizedFitnesses)];
    }
    else if (selectionType == 1) {
        // ranking random selection from top parameter elements
        assert(parameter <= populationSize);
        if (parameter == 0) {
            return rank[0];
        }
        else {
            return rank[rng->drandom(parameter)];
        }
    }
    else if (selectionType == 2) {
        // ranking curved selection
        return NULL;
    }
    else if (selectionType == 3) {
        // tournament selection
        return NULL;
    }
    else if (selectionType == 4) {
        // stochastic universal sampling selection
        return NULL;
    }
    else if (selectionType == 5) {
        // greedy over selection
        return NULL;
    }
    else if (selectionType == 6) {
        // fitness-unaware random selection
        return currentGeneration[(int) (rng->crandom() * evaluated.size())];
    }
    return NULL;
}

/*
    =========
    CROSSOVER
    =========
*/

synthax::algorithm* synthax::gp_population::crossover(unsigned crossoverType, algorithm* one, algorithm* two) {
    if (crossoverType == 0) {
        // standard GP crossover
        node* subtreeone = one->get_random_network_node(rng);
        node* subtreeonecopy = subtreeone->get_copy();
        node* subtreetwo = two->get_random_network_node(rng);
        node* subtreetwocopy = subtreetwo->get_copy();
        one->replace_subtree(subtreeone, subtreetwocopy);
        two->replace_subtree(subtreetwo, subtreeonecopy);
        delete subtreeone;
        delete subtreetwo;

        return NULL;
    }
    else if (crossoverType == 1) {
        return one;
    }
    else if (crossoverType == 2) {
        return two;
    }
    else if (crossoverType == 3) {
        // AM crossover
        /*
        node* newroot = new FunctionNode(multiply, one->get_root(), two->getRoot());
        algorithm* newnet = new algorithm(newroot, "AM crossover");
        return newnet;
        */
        return NULL;
    }
    // experimental array crossover
    else if (crossoverType == 4) {
        return NULL;
    }
    return NULL;
}

void synthax::gp_population::mutate(unsigned mutationType, algorithm* one) {
    if (mutationType == 0) {
        // pick old subtree
        node* forReplacement = one->get_random_network_node(rng);
        assert(params->max_height - forReplacement->depth >= 0);

        // grow new replacement subtree
        node* replacement = growRecursive(0, params->max_height - forReplacement->depth);
        if (params->erc)
            replacement->ephemeral_random(rng);

        // replace and delete old
        one->replace_subtree(forReplacement, replacement);
        delete forReplacement;
    }
    else if (mutationType == 1) {
        // grow new node
        algorithm* two = grow(params->max_initial_height);
        crossover(params->x_type, one, two);
        delete two;
    }
}

void synthax::gp_population::numericallyMutate(algorithm* one) {
    //std::cout << "BEFORE NUMERIC MUTATION " << one->to_string(3) << std::endl;
    double bestProportion = generationBestFitness / generationAverageFitness;
    double temperatureConstant = params->nm_temperature;

    //std::cout << bestProportion << ", " << temperatureConstant << std::endl;

    std::vector<param*>* network_params = one->get_all_mutatable_params();
    for (unsigned i = 0; i < network_params->size(); i++) {
        param* p = network_params->at(i);
        if (p->is_continuous()) {
            double value = p->get_cvalue();
            double min = p->get_cmin();
            double max = p->get_cmax();
            double temperatureFactor = bestProportion * (max - min) * temperatureConstant;
            double rand = rng->crandom();
            double mutationAmount = (rand * temperatureFactor * 2) - temperatureFactor;
            //std::cout << "CONTINUOUS VALUE: " << value << ", MUTATION AMOUNT: " << mutationAmount << ", MIN: " << min << ", MAX: " << max << std::endl;
            p->set_cdata(min, value + mutationAmount, max);
        }
        else {
            int value = p->get_dvalue();
            int min = p->get_dmin();
            int max = p->get_dmax();
            double temperatureFactor = bestProportion * (max - min) * temperatureConstant;
            double rand = rng->crandom();
            double mutationAmount = (rand * temperatureFactor * 2) - temperatureFactor;
            //std::cout << "DISCRETE VALUE: " << value << ", MUTATION AMOUNT: " << mutationAmount << ", MIN: " << min << ", MAX: " << max << std::endl;
            p->set_ddata(min, (int) (value + mutationAmount), max);
        }
    }
    //std::cout << "AFTER NUMERIC MUTATION " << one->to_string(3) << std::endl;
}

synthax::algorithm* synthax::gp_population::newIndividual(unsigned new_type) {
    if (new_type == 0) {
        algorithm* newnet = grow(params->max_initial_height);
        if (params->erc)
            newnet->ephemeral_random(rng);
        return newnet;
    }
    else if (new_type == 1) {
        algorithm* newnet = grow(params->max_height);
        if (params->erc)
            newnet->ephemeral_random(rng);
        return newnet;
    }
    else if (new_type == 2) {
        algorithm* newnet = full(params->max_height);
        if (params->erc)
            newnet->ephemeral_random(rng);
        return newnet;
    }
    else if (new_type == 3) {
        algorithm* newnet = full(params->max_height);
        if (params->erc)
            newnet->ephemeral_random(rng);
        return newnet;
    }
    return NULL;
}

/*
    ====================
    EXTERNAL COMPARATORS
    ====================
*/

bool synthax::compareFitnessesLower(algorithm* one, algorithm* two) {
    return one->fitness < two->fitness;
}

bool synthax::compareFitnessesHigher(algorithm* one, algorithm* two) {
    return two->fitness < one->fitness;
}
