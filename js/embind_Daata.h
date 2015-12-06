#ifndef _EMBIND_DAATA_H
#define _EMBIND_DAATA_H

#include <emscripten/bind.h>
#include "Data.h"

#define Daata_EMSCRIPTEN_BINDINGS(klas) \
      EMSCRIPTEN_BINDINGS(praat_ ## klas)

#define Daata_EMSCRIPTEN_BINDINGS_CLASS(klas) \
  class_<struct##klas, base<structDaata> >(#klas)

#endif
