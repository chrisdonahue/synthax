#ifndef RANDOM_H
#define RANDOM_H

#include "boost/random.hpp"

#include <cmath>
#include <iostream>
#include <vector>

namespace synthax {
	class random {
	public:
		random(unsigned s);

		void normalizeDistribution(std::vector<double>* weights);
		int sampleFromDistribution(std::vector<double>* weights);
		double crandom();
		double whitenoise();
		double gauss();
		int drandom(int m);

	private:
		unsigned seed;
		boost::mt19937 engine;
		boost::uniform_real<double> uni_real;

		// GNU GAUSS MEMBER VARIABLES
		double fac;
		double r;
		double v1;
		double v2;
		double x;
		char s;
	};
}

#endif