#ifndef PRIMITIVES_H
#define PRIMITIVES_H

// effect includes

// envelope includes
#include "primitives/envelope/adsr_x.h"
#include "primitives/envelope/gain.h"
#include "primitives/envelope/lfo_x.h"
#include "primitives/envelope/env_lin_x.h"

// function includes
#include "primitives/function/add.h"
#include "primitives/function/subtract.h"
#include "primitives/function/multiply.h"
#include "primitives/function/sine.h"
#include "primitives/function/cosine.h"

// logic includes
#include "primitives/logic/mixer.h"
#include "primitives/logic/switcher.h"

// modulation includes
#include "primitives/modulation/sin_am.h"
#include "primitives/modulation/sin_pm.h"
#include "primitives/modulation/oscillator/saw_fm.h"
#include "primitives/modulation/oscillator/sin_fm.h"
#include "primitives/modulation/oscillator/sqr_fm.h"
#include "primitives/modulation/oscillator/tri_fm.h"

// terminal includes
#include "primitives/terminal/oscillator/saw_s_gen.h"
#include "primitives/terminal/oscillator/sin_s_gen.h"
#include "primitives/terminal/oscillator/sqr_s_gen.h"
#include "primitives/terminal/oscillator/tri_s_gen.h"
#include "primitives/terminal/adsr.h"
#include "primitives/terminal/constant.h"
#include "primitives/terminal/lfo.h"
#include "primitives/terminal/noise.h"
#include "primitives/terminal/silence.h"
#include "primitives/terminal/env_lin.h"
#include "primitives/terminal/time.h"
#include "primitives/terminal/input_s.h"

#endif
