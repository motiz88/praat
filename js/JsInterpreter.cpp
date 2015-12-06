#include <emscripten/bind.h>
#include "Interpreter.h"

using namespace emscripten;

class JsInterpreter {
  autoInterpreter m_interpreter;
public:
  JsInterpreter():
    m_interpreter(Interpreter_create(nullptr, nullptr))
  {
  }

  void executeScript(std::string text) {
    try {
      Interpreter_run (m_interpreter.peek(), Melder_peek8to32(text.c_str()));
    } catch (MelderError) {
      Melder_throw (U"Script not completed.");
    }
  }
};

// Binding code
EMSCRIPTEN_BINDINGS(praat_js_interpreter) {
  class_<JsInterpreter>("JsInterpreter")
  .constructor<>()
  .function("executeScript", &JsInterpreter::executeScript)
  ;
}