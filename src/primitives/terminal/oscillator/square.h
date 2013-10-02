#ifndef TERMINAL_SQUARE_H
#define TERMINAL_SQUARE_H

#include "../wave_table.h"

namespace synthax{namespace primitive{namespace terminal{
	class square : public synthax::primitive::terminal::wave_table {
	public:
		square(param*, param*, param*);
		~square();

		// node overrides
		square* get_copy();

		// wave table overrides
		void defineHarmonics(int len, int numHarmonics, double* ar, double* ai);
	private:
	};
}}}

#endif
