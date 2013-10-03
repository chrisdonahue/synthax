#ifndef TRI_S_GEN_H
#define TRI_S_GEN_H

#include "../wave_table.h"

namespace synthax{namespace primitive{namespace terminal{
	class tri_s_gen : public synthax::primitive::terminal::wave_table {
	public:
		tri_s_gen(param*, param*, param*);
		~tri_s_gen();

		// node overrides
		tri_s_gen* get_copy();

		// wave table overrides
		void defineHarmonics(int len, int numHarmonics, double* ar, double* ai);
	private:
	};
}}}

#endif
