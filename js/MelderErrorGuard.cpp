#include "MelderErrorGuard.h"
#include "melder.h"

MelderErrorGuard::~MelderErrorGuard()
{
	if (Melder_hasError())
		Melder_flushError();
}