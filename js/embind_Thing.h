#ifndef _EMBIND_THING_H
#define _EMBIND_THING_H

#include <emscripten/bind.h>
#include "Thing.h"

#define Thing_EMSCRIPTEN_BINDINGS(klas) \
      EMSCRIPTEN_BINDINGS(praat_ ## klas)

#define Thing_EMSCRIPTEN_BINDINGS_CLASS(klas) \
  class_<struct##klas, base<structThing> >(#klas)

#endif
