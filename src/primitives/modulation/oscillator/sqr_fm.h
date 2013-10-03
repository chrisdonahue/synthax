#ifndef SQR_FM_H
#define SQR_FM_H

#include "../wave_table_fm.h"

namespace synthax{namespace primitive{namespace modulation{
	class sqr_fm : public synthax::primitive::modulation::wave_table_fm {
	public:
		sqr_fm(param*, param*, param*, node*);
		~sqr_fm();

		// node overrides
		sqr_fm* get_copy();

		// wave table overrides
		void defineHarmonics(int len, int numHarmonics, double* ar, double* ai);
	private:
	};
}}}

#endif
