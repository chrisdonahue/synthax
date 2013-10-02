#ifndef MODULATION_SAW_H
#define MODULATION_SAW_H

#include "../wave_table.h"

namespace synthax{namespace primitive{namespace modulation{
	class saw : public synthax::primitive::modulation::wave_table {
	public:
		saw(param*, param*, param*, node*);
		~saw();

		// node overrides
		saw* get_copy();

		// wave table overrides
		void defineHarmonics(int len, int numHarmonics, double* ar, double* ai);
	private:
	};
}}}

#endif
