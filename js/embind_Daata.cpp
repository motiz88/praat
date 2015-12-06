#include "embind_Daata.h"

#include <emscripten/bind.h>
#include "praat.h"
#include "Data.h"
#include "embind_Thing.h"

using namespace emscripten;

// Binding code
EMSCRIPTEN_BINDINGS(praat_Daata) {
  class_<structThing>("Thing");
  Thing_EMSCRIPTEN_BINDINGS_CLASS(Daata)
	.function("getNrow", &structDaata::v_getNrow)
	.function("getNcol", &structDaata::v_getNcol)
	.function("getXmin", &structDaata::v_getXmin)
	.function("getXmax", &structDaata::v_getXmax)
	.function("getYmin", &structDaata::v_getYmin)
	.function("getYmax", &structDaata::v_getYmax)
	.function("getNx", &structDaata::v_getNx)
	.function("getNy", &structDaata::v_getNy)
	.function("getDx", &structDaata::v_getDx)
	.function("getDy", &structDaata::v_getDy)
	.function("getX", &structDaata::v_getX)
	.function("getY", &structDaata::v_getY)
	// .function("getRowStr", &structDaata::v_getRowStr)
	// .function("getColStr", &structDaata::v_getColStr)
	.function("getCell", &structDaata::v_getCell)
	// .function("getCellStr", &structDaata::v_getCellStr)
	.function("getVector", &structDaata::v_getVector)
	// .function("getVectorStr", &structDaata::v_getVectorStr)
	.function("getMatrix", &structDaata::v_getMatrix)
	// .function("getMatrixStr", &structDaata::v_getMatrixStr)
	// .function("getFunction0", &structDaata::v_getFunction0)
	// .function("getFunction1", &structDaata::v_getFunction1)
	// .function("getFunction2", &structDaata::v_getFunction2)
	// .function("getRowIndex", &structDaata::v_getRowIndex)
	// .function("getColIndex", &structDaata::v_getColIndex)
	;
}