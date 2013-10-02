#ifndef GPSYNTH_H
#define GPSYNTH_H

#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include "../Common/GPLogger.h"
#include "../Common/random.h"
#include "algorithm.h"

struct GPSynthParams {
    // synth evolution parameters
    unsigned population_size;
    unsigned max_initial_height;
    unsigned max_height;
    bool erc;
    bool backup_all_networks;
    unsigned backup_precision;

    // fitness landscape parameters
    double best_possible_fitness;
    bool lower_fitness_is_better;

    // synth genetic parameters
    // numeric mutation
    double nm_proportion;
    double nm_temperature;
    unsigned nm_selection_type;
    double nm_selection_percentile;
    // mutation
    double mu_proportion;
    unsigned mu_type;
    unsigned mu_selection_type;
    double mu_selection_percentile;
    // crossover
    double x_proportion;
    unsigned x_type;
    unsigned x_selection_type;
    double x_selection_percentile;
    // reproduction
    double re_proportion;
    unsigned re_selection_type;
    double re_selection_percentile;
    bool re_reevaluate;
    // random new individual
    double new_proportion;
    unsigned new_type;
};

class GPSynth {
public:
    // construction
    GPSynth(GPLogger* logger, GPSynthParams* params, random* rng, std::vector<node*>* primitives);
    ~GPSynth();

    // EVOLUTION CONTROL
    algorithm* getIndividual();
    void getIndividuals(std::vector<algorithm*>& networks);
    int assignFitness(algorithm* net, double fitness);
	algorithm* growNewIndividual(unsigned maxHeight);
	bool replaceIndividual(algorithm* old, algorithm* nu);
    int prevGeneration();
    void endGeneration();
    void printGenerationDelim();
    void printGenerationSummary();
    void printEvolutionSummary();
    void getCurrentGeneration(std::vector<algorithm*>& networks);

    // PUBLIC EVOLUTION STATE
    int currentGenerationNumber;
    algorithm* generationChamp;
    algorithm* champ;

private:
    // construction
    node* fullRecursive(unsigned cd, unsigned d);
    algorithm* full(unsigned d);
    node* growRecursive(unsigned cd, unsigned m);
    algorithm* grow(unsigned m);
    void initPopulation();

    // EVOLUTION CONTROL
    int nextGeneration();
    void calculateGenerationRanks();
    void calculateGenerationNormalizedFitnesses();

    // helpers
    void addNetworkToPopulation(algorithm* net);
    void clearGenerationState();
    algorithm* selectFromEvaluated(unsigned selectionType, unsigned parameter);

    // GENETIC OPERATIONS
    algorithm* crossover(unsigned crossoverType, algorithm* one, GPNetwork* two);
    void mutate(unsigned mutationType, algorithm* one);
    void numericallyMutate(algorithm* one);
    algorithm* newIndividual(unsigned new_type);

    // PRIVATE EVOLUTION STATE
    GPLogger* logger;
    GPSynthParams* params;
    random* rng;
    unsigned populationSize;
    int nextNetworkid;
    bool lowerFitnessIsBetter;
    double overallBestFitness;
    double generationBestFitness;
    double generationAverageFitness;
    bool currentGenerationAlive;

    // CONVERGENCE-VARYING
    double convergenceFactor;
    std::vector<double*> continuousConvergenceVaryingParams;
    std::vector<double*> continuousConvergenceVaryingTemperatures;

    // AVAILABLE CONTAINERS
    std::vector<node*>* availablePrimitives;
    std::vector<node*>* availableFunctions;
    std::vector<node*>* availableTerminals;

    // NETWORK CONTAINERS
    std::vector<std::string> allNetworks;
    std::set<algorithm*> unevaluated;
    std::set<algorithm*> evaluated;
    std::map<int, algorithm*> currentGeneration;

    // SELECTION CONTAINERS
    std::vector<double> rawFitnesses;
    std::vector<double> normalizedFitnesses;
    std::vector<algorithm*> rank;
};

// EXTERNAL COMPARATORS
extern bool compareFitnessesLower(algorithm* one, algorithm* two);
extern bool compareFitnessesHigher(algorithm* one, algorithm* two);

#endif
