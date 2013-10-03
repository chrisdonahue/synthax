#ifndef SQR_S_GEN_H
#define SQR_S_GEN_H

#include "../wave_table.h"

namespace synthax{namespace primitive{namespace terminal{
	class sqr_s_gen : public synthax::primitive::terminal::wave_table {
	public:
		sqr_s_gen(param*, param*, param*);
		~sqr_s_gen();

		// node overrides
		sqr_s_gen* get_copy();

		// wave table overrides
		void defineHarmonics(int len, int numHarmonics, double* ar, double* ai);
	private:
	};
}}}

#endif