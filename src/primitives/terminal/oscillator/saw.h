#ifndef TERMINAL_SAW_H
#define TERMINAL_SAW_H

#include "../wave_table.h"

namespace synthax{namespace primitive{namespace terminal{
	class saw : public synthax::primitive::terminal::wave_table {
	public:
		saw(param*, param*, param*);
		~saw();

		// node overrides
		saw* get_copy();

		// wave table overrides
		void defineHarmonics(int len, int numHarmonics, double* ar, double* ai);
	private:
	};
}}}

#endif
