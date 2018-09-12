#include "mathlib_config.h"

#if (IX86_CPU)
#   include "IX86_endian.h"
#elif MATHLIB_AIX
#    include "AIX_endian.h"
#elif MATHLIB_SUN
#    include "SUN_endian.h"
#elif MATHLIB_BORLANDC
#     include "BCB_endian.h"
#elif MATHLIB_MSVC
#     include "MSVC_endian.h"
#else
#error "Unsupported platform"
#endif
