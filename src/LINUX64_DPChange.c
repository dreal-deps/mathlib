/****************************************************************************/
/*                                                                          */
/*MODULE_NAME:DPChange                                                      */
/*                                                                          */
/*FUNCTIONS:Init_Lib                                                        */
/*          Exit_Lib                                                        */
/*                                                                          */
/* Init_lib must be called once prior to any usage of the mathlib routines. */
/* Exit_lib must be called once after the last usage of the mathlib         */
/* routines.                                                                */
/* Init_Lib changes the control word to IEEE double precision so that the   */
/* math routines will work properly. It returns the original status         */
/* as unsigned short. The returned value should be handed to Exit_lib       */
/* in order to restore the original status of the control word after the    */
/* math routines are no longer needed                                       */
/****************************************************************************/
#include "DPChange.h"
#include <stdio.h>
#if HAVE_FENV_H
#  include <fenv.h>
#endif /* HAVE_FENV_H */

/* 
	Temporary workaround for linkage problems with fegetenv()/fesetenv().
	Definition of local copies of fegetenv()/fesetenv() if the macro 
	GETENV_WORKAROUND is set to 1
*/
#define GETENV_WORKAROUND 0
#if GETENV_WORKAROUND
# define FESETENV mathlib_fesetenv
# define FEGETENV mathlib_fegetenv

  static int mathlib_fegetenv (fenv_t *envp)
  {
	 __asm__ ("fnstenv %0\n"
				 "stmxcsr %1" : "=m" (*envp), "=m" (envp->__mxcsr));
	 /* Success.  */
	 return 0;
  }
  
static int mathlib_fesetenv (const fenv_t *envp)
{
  fenv_t temp;

  /* Install the environment specified by ENVP.  But there are a few
     values which we do not want to come from the saved environment.
     Therefore, we get the current environment and replace the values
     we want to use from the environment specified by the parameter.  */
  __asm__ ("fnstenv %0\n"
	   "stmxcsr %1" : "=m" (*&temp), "=m" (*&temp.__mxcsr));

  if (envp == FE_DFL_ENV)
    {
      temp.__control_word |= FE_ALL_EXCEPT;
      temp.__control_word &= ~FE_TOWARDZERO;
      temp.__status_word &= ~FE_ALL_EXCEPT;
      temp.__eip = 0;
      temp.__cs_selector = 0;
      temp.__opcode = 0;
      temp.__data_offset = 0;
      temp.__data_selector = 0;
      /* Set mask for SSE MXCSR.  */
      temp.__mxcsr |= (FE_ALL_EXCEPT << 7);
      /* Set rounding to FE_TONEAREST.  */
      temp.__mxcsr &= ~ 0x6000;
      temp.__mxcsr |= (FE_TONEAREST << 3);
    }
  else if (envp == ((const fenv_t *) -2))
    {
      temp.__control_word &= ~(FE_ALL_EXCEPT | FE_TOWARDZERO);
      temp.__status_word &= ~FE_ALL_EXCEPT;
      temp.__eip = 0;
      temp.__cs_selector = 0;
      temp.__opcode = 0;
      temp.__data_offset = 0;
      temp.__data_selector = 0;
      /* Set mask for SSE MXCSR.  */
      /* Set rounding to FE_TONEAREST.  */
      temp.__mxcsr &= ~ 0x6000;
      temp.__mxcsr |= (FE_TONEAREST << 3);
      /* Do not mask exceptions.  */
      temp.__mxcsr &= ~(FE_ALL_EXCEPT << 7);
    }
  else
    {
      temp.__control_word &= ~(FE_ALL_EXCEPT | FE_TOWARDZERO);
      temp.__control_word |= (envp->__control_word
			      & (FE_ALL_EXCEPT | FE_TOWARDZERO));
      temp.__status_word &= ~FE_ALL_EXCEPT;
      temp.__status_word |= envp->__status_word & FE_ALL_EXCEPT;
      temp.__eip = envp->__eip;
      temp.__cs_selector = envp->__cs_selector;
      temp.__opcode = envp->__opcode;
      temp.__data_offset = envp->__data_offset;
      temp.__data_selector = envp->__data_selector;
      temp.__mxcsr = envp->__mxcsr;
    }

  __asm__ ("fldenv %0\n"
	   "ldmxcsr %1" : : "m" (temp), "m" (temp.__mxcsr));
  return 0;
}
#else
# define FESETENV fesetenv
# define FEGETENV fegetenv
#endif /* GETENV_WORKAROUND */




unsigned  short OrgDPStatus=0;
unsigned  short NewDPStatus=0;

#if MATHLIB_MINGW
#  define ORG_DP_STATUS "_OrgDPStatus"
#  define NEW_DP_STATUS "_NewDPStatus"
#else
#  define ORG_DP_STATUS "OrgDPStatus"
#  define NEW_DP_STATUS "NewDPStatus"
#endif


#define CTRLWORD(v) (v).__control_word

/* Function to change precision control to double and round mode to nearest */
/* or even. Function returns unsigned short between 0 and 15 that indicates */
/* the original round control and precision mode before the change.         */
/* The two LSB bits of the returned value are the precision mode, and the   */
/* next two bits are the round control.                                     */

unsigned short Init_Lib()
{
#if HAVE_FENV_H
  	fenv_t status, tmp;
	unsigned short tempStatus;
	FEGETENV(&status);
	OrgDPStatus = CTRLWORD(status);
	tempStatus =  OrgDPStatus & MaskClearDPR; /* clear relevant 4 bits */
	NewDPStatus=tempStatus | MaskSetDPR;  /* compute required values */
	CTRLWORD(status) = NewDPStatus;
	FESETENV(&status);
	FEGETENV(&tmp);
  	OrgDPStatus= OrgDPStatus & MaskDPR;     /* select only bits 8-11 */
  	OrgDPStatus= OrgDPStatus >> 8 ;     /* now relevant bits are 0-3 */
  	return OrgDPStatus;
#else 
#   error "fenv.h not found and no replacement available to initialize the library"
#endif /* HAVE_FENV_H */
}


/* Function that receives an unsigned short argument in the range 0 - 15    */
/* and changes the precision control and round mode according to the        */
/* explanation above. If the value is more than 15 it prints to stdout an   */
/* error message and changes nothing.                                       */

void Exit_Lib(unsigned short status)
{
#if HAVE_FENV_H
  	fenv_t cpustatus;
  	unsigned short LocalStatus = status;            /* local copy of argument */
  	if (LocalStatus>15)                /*unsigned is always greater than zero */
    {
    	printf("Exit_Lib: argument > 15 error, status=%d\n", LocalStatus);
     	return;
    }
	FEGETENV(&cpustatus);
	NewDPStatus = CTRLWORD(cpustatus);
  	LocalStatus = LocalStatus << 8; /* since value is less than 16 the only    */
                                  /* non-zero bits are in positions 0-3      */
      /* after the <<8 the precision and rounding bits are in positions 8-11 */
  	NewDPStatus = NewDPStatus & MaskClearDPR;        /* clearing relevant bits */
  	OrgDPStatus = NewDPStatus | LocalStatus;     /* resetting to org DPR staus */
	CTRLWORD(cpustatus) = OrgDPStatus;
	FESETENV(&cpustatus);
  	return;
#else 
#   error "fenv.h not found and no replacement available to deinitialize the library"
#endif /* HAVE_FENV_H */
}













































