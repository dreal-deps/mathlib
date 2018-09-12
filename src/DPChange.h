#include "mathlib_config.h"

#if (MATHLIB_LINUX || MATHLIB_MINGW)
#   include "LINUX_DPChange.h"
#elif MATHLIB_I86_MACOSX
#   include "IX86MACOSX_DPChange.h"
#elif MATHLIB_MSVC
#     include "MSVC_DPChange.h"
#endif
