#ifndef SIN_S_GEN_H
#define SIN_S_GEN_H

#include "../wave_table.h"

namespace synthax{namespace primitive{namespace terminal{
	class sin_s_gen : public synthax::primitive::terminal::wave_table {
	public:
		sin_s_gen(param*, param*, param*);
		~sin_s_gen();

		// node overrides
		sin_s_gen* get_copy();

		// wave table overrides
		void defineHarmonics(int len, int numHarmonics, double* ar, double* ai);
	private:
	};
}}}

#endif