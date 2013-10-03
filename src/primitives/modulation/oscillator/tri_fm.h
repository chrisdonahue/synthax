#ifndef TRI_FM_H
#define TRI_FM_H

#include "../wave_table_fm.h"

namespace synthax{namespace primitive{namespace modulation{
	class tri_fm : public synthax::primitive::modulation::wave_table_fm {
	public:
		tri_fm(param*, param*, param*, node*);
		~tri_fm();

		// node overrides
		tri_fm* get_copy();

		// wave table overrides
		void defineHarmonics(int len, int numHarmonics, double* ar, double* ai);
	private:
	};
}}}

#endif