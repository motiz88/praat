#include <emscripten/bind.h>
#include "praat.h"
#include "Data.h"
#include "embind_Thing.h"
#include "embind_Daata.h"

using namespace emscripten;

namespace js {
  void praat_new (std::unique_ptr<structDaata> me) {
    ::praat_new(std::move(me));
  }
}

// Binding code
EMSCRIPTEN_BINDINGS(praat_Objects) {
  function("praat_new", select_overload<void(std::unique_ptr<structDaata>)>(&js::praat_new));
  function("praat_updateSelection", *praat_updateSelection);
}