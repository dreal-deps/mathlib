/**************************************************************************/
/*                                                                        */ 
/*MODULE_NAME:DPChange                                                    */
/*                                                                        */
/*FUNCTIONS:Init_Lib                                                      */
/*          Exit_Lib                                                      */
/*                                                                        */
/*  common data & function prototypes                                     */ 
/**************************************************************************/
#ifndef DP
#define DP
/* Round Control    : bits 10 and 11 of the control word  */                  
/* Precision Control: bits  8 and  9 of the control word  */


/* Mask to clear round and precision control */
#define MaskClearDPR 0xf0ff  /*Binary   1111000011111111 */

/* Mask to set precision to double and round control to nearest or even */
#define MaskSetDPR   0x0200  /* Binary  0000001000000000 */

/* Mask to clear all bits except round control and precision mode */
#define MaskDPR      0x0f00  /* Binary  0000111100000000 */

/* The floating point mode of the processor is controlled by a control word */
/* and is set to defaults by init routines inserted by the compiler. The    */
/* x86/Linux/gcc default FP mode is x86/extended-double. This version of    */
/* the library requires the IEEE double and not the x86/extended-double.    */
/* Function to change precision control to double and round mode to nearest */
/* or even. Function returns unsigned short between 0 and 15 that indicates */
/* the original round control and precision mode before the change.         */
/* The two LSB bits of the returned value are the precision mode, and the   */
/* next two bits are the round control.                                     */

extern unsigned short Init_Lib();

/* Function that receives an unsigned short argument in the range 0 - 15    */
/* and changes the precision control and round mode according to the        */
/* explanation above. If the value is more than 15 it prints to stdout an   */
/* error message and changes nothing.                                       */

extern void Exit_Lib(unsigned short);

#endif /*DP*/
