#ifndef SIN_FM_H
#define SIN_FM_H

#include "../wave_table_fm.h"

namespace synthax{namespace primitive{namespace modulation{
	class sin_fm : public synthax::primitive::modulation::wave_table_fm {
	public:
		sin_fm(param*, param*, param*, node*);
		~sin_fm();

		// node overrides
		sin_fm* get_copy();

		// wave table overrides
		void defineHarmonics(int len, int numHarmonics, double* ar, double* ai);
	private:
	};
}}}

#endif
