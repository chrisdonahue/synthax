#ifndef PARAM_H
#define PARAM_H

#include "random.h"

#include <assert.h>
#include <sstream>
#include <string>

namespace synthax {
	class param {
	public:
		// discrete constructor
		param(std::string t, bool mut, int val, int min, int max) {
			assert(!mut || (min <= val && val <= max));
			type = t;
			continuous = false;
			mutatable = mut;
			instantiate();
			dvalue = val;
			dminimum = min;
			dmaximum = max;
		}

		// continuous constructor
		param(std::string t, bool mut, float val, float min, float max) {
			assert(!mut || (min <= val && val <= max));
			type = t;
			continuous = true;
			mutatable = mut;
			instantiate();
			cvalue = val;
			cminimum = min;
			cmaximum = max;
		}

		~param() {
		}

		// copy method
		param* get_copy() {
			if (continuous)
				return new param(type, mutatable, cvalue, cminimum, cmaximum);
			else
				return new param(type, mutatable, dvalue, dminimum, dmaximum);
		}

		// render to a string stream
		void to_string(std::stringstream& ss) {
			ss << "{";
			if (continuous) {
				ss << "c ";

				if (min_null)
					ss << "null ";
				else
					ss << cminimum << " ";

				if (value_null)
					ss << "null ";
				else
					ss << cvalue << " ";

				if (max_null)
					ss << "null";
				else
					ss << cmaximum;
			}
			else {
				ss << "d ";

				if (min_null)
					ss << "null ";
				else
					ss << dminimum << " ";

				if (value_null)
					ss << "null ";
				else
					ss << dvalue << " ";

				if (max_null)
					ss << "null";
				else
					ss << dmaximum;

			}
			ss << "}";
		}

		// get param as string
		std::string to_string(unsigned precision) {
			std::stringstream ss;
			ss.precision(precision);
			to_string(ss);
			return ss.str();
		}

		// type
		void set_type(std::string newtype) {
			type = newtype;
		}

		std::string get_type() {
			return type;
		}

		// mutatable
		void set_mutatable() {
			mutatable = true;
		}

		void set_unmutatable() {
			mutatable = false;
		}

		bool is_mutatable() {
			return mutatable;
		}

		bool is_unmutatable() {
			return !mutatable;
		}

		// continuous
		bool is_continuous() {
			return continuous;
		}

		bool is_discrete() {
			return !continuous;
		}

		// instatiated
		bool is_instantiated() {
			return !(min_null || value_null || max_null);
		}

		bool is_uninstantiated() {
			return (min_null || value_null || max_null);
		}

		// null
		void set_val_null() {
			value_null = true;
		}

		void set_min_null() {
			min_null = true;
		}

		void set_max_null() {
			max_null = true;
		}

		bool has_val_null() {
			return value_null;
		}

		bool has_min_null() {
			return min_null;
		}

		bool has_max_null() {
			return max_null;
		}

		// set discrete data
		void set_ddata(int min, int val, int max) {
			assert(!continuous);
			assert(!mutatable || (min <= val && val <= max));
			instantiate();
			dminimum = min;
			dvalue = val;
			dmaximum = max;
		}

		// set continuous value
		void set_dvalue(int newvalue) {
			assert(!continuous);
			assert(dminimum <= newvalue || min_null);
			assert(newvalue <= dmaximum || max_null);
			value_null = false;
			dvalue = newvalue;
		}

		// set continuous data
		void set_cdata(float min, float val, float max) {
			assert(continuous);
			assert(!mutatable || (min <= val && val <= max));
			instantiate();
			cminimum = min;
			cvalue = val;
			cmaximum = max;
		}

		// set continuous value
		void set_cvalue(float newvalue) {
			assert(continuous);
			assert(cminimum <= newvalue || min_null);
			assert(newvalue <= cmaximum || max_null);
			value_null = false;
			cvalue = newvalue;
		}

		// continuous accessors
		float get_cvalue() {
			assert(continuous);
			assert(!value_null);
			return cvalue;
		}

		float get_cmin() {
			assert(continuous);
			assert(!min_null);
			return cminimum;
		}

		float get_cmax() {
			assert(continuous);
			assert(!max_null);
			return cmaximum;
		}

		// discrete accessors
		int get_dvalue() {
			assert(!continuous);
			assert(!value_null);
			return dvalue;
		}

		int get_dmin() {
			assert(!continuous);
			assert(!min_null);
			return dminimum;
		}

		int get_dmax() {
			assert(!continuous);
			assert(!max_null);
			return dmaximum;
		}

		// combined accessors
		float get_value() {
			assert(!value_null);
			if (continuous)
				return cvalue;
			else
				return (float) dvalue;
		}

		float get_min() {
			assert(!min_null);
			if (continuous)
				return cminimum;
			else
				return (float) dminimum;
		}

		float get_max() {
			assert(!max_null);
			if (continuous)
				return cmaximum;
			else
				return (float) dmaximum;
		}

		// randomize
		void ephemeral_random(random* rng) {
			if (continuous && mutatable)
				cvalue = ((float) rng->crandom() * (cmaximum - cminimum)) + cminimum;
			else if (!continuous && mutatable)
				dvalue = (rng->drandom((dmaximum - dminimum) + 1)) + dminimum;
			value_null = false;
		}

	private:
		inline void instantiate() {
			value_null = false;
			min_null = false;
			max_null = false;
		}
    
		std::string type;

		bool continuous;
		bool mutatable;

		bool value_null;
		bool min_null;
		bool max_null;

		int dvalue;
		int dminimum;
		int dmaximum;

		float cvalue;
		float cminimum;
		float cmaximum;
	};
}

#endif