#ifndef SAW_FM_H
#define SAW_FM_H

#include "../wave_table_fm.h"

namespace synthax{namespace primitive{namespace modulation{
	class saw_fm : public synthax::primitive::modulation::wave_table_fm {
	public:
		saw_fm(param*, param*, param*, node*);
		~saw_fm();

		// node overrides
		saw_fm* get_copy();

		// wave table overrides
		void defineHarmonics(int len, int numHarmonics, double* ar, double* ai);
	private:
	};
}}}

#endif
