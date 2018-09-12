/****************************************************************************/
/*                                                                          */ 
/*MODULE_NAME:DPChange.c                                                     */
/*                                                                          */
/*FUNCTIONS:Init_Lib                                                        */
/*          Exit_Lib                                                        */
/*                                                                          */
/* Routines are place holders for future use                                */
/* Init_Lib changes the control word to IEEE double precision so that the   */
/* math routines will work properly. It returns the original status         */
/* as unsigned short. The returned value should be handed to Exit_lib       */
/* in order to restore the original status of the control word after the    */
/* math routines are no longer needed                                       */
/****************************************************************************/
#include "DPChange.h"


/* see further comments in the DPChange.h file                              */

/* Function does nothing, it only returns a meaningless value of 0          */
/* Function is only a placeholder for future use                            */
unsigned short Init_Lib()    
{
  return 0;
}  

/* Function does nothing.                                                   */
/* Function is only a placeholder for future use                            */
void Exit_Lib(unsigned short status) 
{ 
  return;
}
