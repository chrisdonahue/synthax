#ifndef MODULATION_SINE_H
#define MODULATION_SINE_H

#include "../wave_table.h"

namespace synthax{namespace primitive{namespace modulation{
	class sine : public synthax::primitive::modulation::wave_table {
	public:
		sine(param*, param*, param*, node*);
		~sine();

		// node overrides
		sine* get_copy();

		// wave table overrides
		void defineHarmonics(int len, int numHarmonics, double* ar, double* ai);
	private:
	};
}}}

#endif
