#ifndef MODULATION_SQUARE_H
#define MODULATION_SQUARE_H

#include "../wave_table.h"

namespace synthax{namespace primitive{namespace modulation{
	class square : public synthax::primitive::modulation::wave_table {
	public:
		square(param*, param*, param*, node*);
		~square();

		// node overrides
		square* get_copy();

		// wave table overrides
		void defineHarmonics(int len, int numHarmonics, double* ar, double* ai);
	private:
	};
}}}

#endif
