#ifndef SAW_S_GEN_H
#define SAW_S_GEN_H

#include "../wave_table.h"

namespace synthax{namespace primitive{namespace terminal{
	class saw_s_gen : public synthax::primitive::terminal::wave_table {
	public:
		saw_s_gen(param*, param*, param*);
		~saw_s_gen();

		// node overrides
		saw_s_gen* get_copy();

		// wave table overrides
		void defineHarmonics(int len, int numHarmonics, double* ar, double* ai);
	private:
	};
}}}

#endif