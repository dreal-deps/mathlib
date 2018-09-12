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
#include "MathLib.h"
#include "DPChange.h"

#include <stdio.h>

unsigned  short OrgDPStatus=0;
unsigned  short NewDPStatus=0;


/* Function to change precision control to double and round mode to nearest */
/* or even. Function returns unsigned short between 0 and 15 that indicates */
/* the original round control and precision mode before the change.         */
/* The two LSB bits of the returned value are the precision mode, and the   */
/* next two bits are the round control.                                     */

unsigned short Init_Lib()
{
  unsigned short tempStatus;
/* get original status word            */
  __asm {
    fstcw WORD PTR OrgDPStatus
  } 
  tempStatus= OrgDPStatus & MaskClearDPR; /* clear relevant 4 bits */
  NewDPStatus=tempStatus | MaskSetDPR;  /* compute required values */
 /* set control word to required value */
  __asm {
    fldcw WORD PTR NewDPStatus
  }
  OrgDPStatus= OrgDPStatus & MaskDPR;     /* select only bits 8-11 */
  OrgDPStatus= OrgDPStatus >> 8 ;     /* now relevant bits are 0-3 */
  return OrgDPStatus;
}  


/* Function that receives an unsigned short argument in the range 0 - 15    */
/* and changes the precision control and round mode according to the        */
/* explanation above. If the value is more than 15 it prints to stdout an   */
/* error message and changes nothing.                                       */

void Exit_Lib(unsigned short status)
{ 
  unsigned short LocalStatus = status;            /* local copy of argument */
  if (LocalStatus>15)                /*unsigned is always greater than zero */
    {
     printf("Exit_Lib: argument > 15 error, status=%d\n", LocalStatus);
     return;
    }  
  __asm {
    fstcw WORD PTR NewDPStatus
  }
  LocalStatus = LocalStatus << 8; /* since value is less than 16 the only    */
                                  /* non-zero bits are in positions 0-3      */
      /* after the <<8 the precision and rounding bits are in positions 8-11 */
  NewDPStatus = NewDPStatus & MaskClearDPR;        /* clearing relevant bits */
  OrgDPStatus = NewDPStatus | LocalStatus;     /* resetting to org DPR staus */
  /* setting the processor control word */
  __asm {
    fldcw WORD PTR OrgDPStatus
  }
  return;
}













































