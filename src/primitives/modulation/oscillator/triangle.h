#ifndef MODULATION_TRIANGLE_H
#define MODULATION_TRIANGLE_H

#include "../wave_table.h"

namespace synthax{namespace primitive{namespace modulation{
	class triangle : public synthax::primitive::modulation::wave_table {
	public:
		triangle(param*, param*, param*, node*);
		~triangle();

		// node overrides
		triangle* get_copy();

		// wave table overrides
		void defineHarmonics(int len, int numHarmonics, double* ar, double* ai);
	private:
	};
}}}

#endif
