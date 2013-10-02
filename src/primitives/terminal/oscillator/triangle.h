#ifndef TERMINAL_TRIANGLE_H
#define TERMINAL_TRIANGLE_H

#include "../wave_table.h"

namespace synthax{namespace primitive{namespace terminal{
	class triangle : public synthax::primitive::terminal::wave_table {
	public:
		triangle(param*, param*, param*);
		~triangle();

		// node overrides
		triangle* get_copy();

		// wave table overrides
		void defineHarmonics(int len, int numHarmonics, double* ar, double* ai);
	private:
	};
}}}

#endif
