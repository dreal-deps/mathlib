#include "mathlib_config.h"

#if ((MATHLIB_LINUX || MATHLIB_MINGW) && !X86_64BITS)
#   include "LINUX_DPChange.c"
#elif (MATHLIB_LINUX && X86_64BITS)
#   include "LINUX64_DPChange.c"
#elif MATHLIB_I86_MACOSX
#   include "IX86MACOSX_DPChange.c"
#elif MATHLIB_MSVC
#     include "MSVC_DPChange.c"
#endif
