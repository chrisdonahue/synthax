#ifndef PARAM_H
#define PARAM_H

#include "../common/random.h"

#include <assert.h>
#include <sstream>
#include <string>

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

            if (minimum_null)
                ss << "null ";
            else
                ss << cminimum << " ";

            if (value_null)
                ss << "null ";
            else
                ss << cvalue << " ";

            if (maximum_null)
                ss << "null";
            else
                ss << cmaximum;
        }
        else {
            ss << "d ";

            if (minimum_null)
                ss << "null ";
            else
                ss << dminimum << " ";

            if (value_null)
                ss << "null ";
            else
                ss << dvalue << " ";

            if (maximum_null)
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
        return instantiated;
    }

    bool is_uninstantiated() {
        return !instantaited;
    }

    // null
    void set_value_null() {
        instantiated = false;
        value_null = true;
    }

    void set_minimum_null() {
        instantiated = false;
        minimum_null = true;
    }

    void set_value_null() {
        instantiated = false;
        maximum_null = true;
    }

    bool has_value_null() {
        return value_null;
    }

    bool has_minimum_null() {
        return minimum_null;
    }

    bool has_maximum_null() {
        return maximum_null;
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
        set_ddata(dminimum, newvalue, dmaximum);
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
        set_cdata(cminimum, newvalue, cmaximum);
    }

    // continuous accessors
    float get_cvalue() {
        assert(continuous);
        assert(!value_null);
        return cvalue;
    }

    float get_cmin() {
        assert(continuous);
        assert(!minimum_null);
        return cminimum;
    }

    float get_cmax() {
        assert(continuous);
        assert(!maximum_null);
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
        assert(!minimum_null);
        return dminimum;
    }

    int get_dmax() {
        assert(!continuous);
        assert(!maximum_null);
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
        assert(!minimum_null);
		if (continuous)
			return cminimum;
		else
			return (float) dminimum;
    }

    float get_max() {
        assert(!maximum_null);
		if (continuous)
			return cmaximum;
		else
			return (float) dmaximum;
    }

    // randomize
    void ephemeral_random(random* rng) {
        if (continuous && mutatable)
            cvalue = ((float) rng->random() * (cmaximum - cminimum)) + cminimum;
        else if (!continuous && mutatable)
            dvalue = (rng->random((dmaximum - dminimum) + 1)) + dminimum;
    }

private:
    void instantiate() {
        instantiated = true;
        value_null = false;
        minimum_null = false;
        maximum_null = false;
    }
    
    std::string type;

    bool continuous;
    bool mutatable;
    bool instantiated;

    bool value_null;
    bool minimum_null;
    bool maximum_null;

    int dvalue;
    int dminimum;
    int dmaximum;

    float cvalue;
    float cminimum;
    float cmaximum;
};

#endif
