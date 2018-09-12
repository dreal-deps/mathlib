#undef PACKAGE
#undef VERSION


#if defined (_MSC_VER) /* Windows / Visual C++ */
#   ifndef _MATHLIB_DLL_
#      define _MATHLIB_DLL_ extern __declspec(dllexport)
#   endif
#   include "mathlib_config_msvc.h"
//
#elif defined (__MINGW32__) /* MinGW */
# ifndef _MATHLIB_DLL_
#   define _MATHLIB_DLL_
# endif
# include "mathlib_config_mingw.h"
#else /* Other: presumably Linux/gcc/autoconf */
# ifndef _MATHLIB_DLL_
#   define _MATHLIB_DLL_
# endif
# include "mathlib_configuration.h"
#endif
