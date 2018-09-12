/**************************************************************************/
/*                                                                        */ 
/*MODULE_NAME:DPChange                                                    */
/*                                                                        */
/*FUNCTIONS:Init_Lib                                                      */
/*          Exit_lib                                                      */
/*                                                                        */
/*  common data & function prototypes                                     */ 
/**************************************************************************/
#ifndef DP
#define DP

/* The floating point mode of the processor is controlled by a control word */
/* and is set to defaults by init routines inserted by the compiler. The    */
/* Sun/Solaris/gcc default FP mode is IEEE double. This version of the      */
/* math lib requires the IEEE double mode, therefore the Init_Lib() and the */
/* Exit_lib() functions for the AIX do nothing.                             */
/* These functions are here for uniformity and compatibility of usage with  */
/* other platforms such as the x86/Linux and  x86/NT.                       */

/* Function returns 0. The return value is meaningless                      */
/* Function is a placeholder for future SUN processor FP modes          */
unsigned short Init_Lib();

/* Function does nothing                                                    */
/* Function is a placeholder for future PowerPC processor FP modes          */
void Exit_Lib(unsigned short);
#endif /*DP*/
