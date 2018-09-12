
/*
 * IBM Accurate Mathematical Library
 * Copyright (c) International Business Machines Corp., 2001
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or 
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  
 */
/************************************************************************/
/*  MODULE_NAME: trigo.h                                                */
/*                                                                      */
/*                                                                      */
/* 	trigonometric constants for BIG or LITTLE ENDIAN                */
/************************************************************************/


#ifdef BIG_ENDI
static const mynumber
/**/            hp0 = {0x3FF921FB, 0x54442D18 }, /* PI / 2                 */
/**/            hp1 = {0x3C91A626, 0x33145C07 }, /* 6.123233995736766e-17  */
/**/            hp2 = {0xb91f1976, 0xb7ed8fbc}, 

/**/            pi0 = {0x400921FB, 0x54442D18 }, /* PI                     */
/**/            pi1 = {0x3CA1A626, 0x33145C07 }, 
/**/            pi2 = {0xb92f1976, 0xb7ed8fbc}, 

/**/            mp1 = {0x3FF921FB, 0x58000000 }, /*  1.5707963407039642      */
/**/            mp2 = {0xBE4DDE97, 0x3C000000 }, /* -1.3909067564377153e-08  */
/**/            mp3 = {0xBC8CB3B3, 0x99D747F2 }, /* -4.9789962505147994e-17  */
/**/            pp3 = {0xBC8CB3B3, 0x98000000 }, /* -4.9789962314799099e-17  */
/**/            pp4 = {0xbacd747f, 0x23e32ed7 }, /* -1.9034889620193266e-25  */
/**/          hpinv = {0x3FE45F30, 0x6DC9C883 }, /*  0.63661977236758138     */
/**/          toint = {0x43380000, 0x00000000 }; /*  6755399441055744        */

#else
#ifdef LITTLE_ENDI
static const mynumber
/**/            hp0 = {0x54442D18, 0x3FF921FB }, /* PI / 2                 */
/**/            hp1 = {0x33145C07, 0x3C91A626 }, /* 6.123233995736766e-17  */
/**/            hp2 = {0xb7ed8fbc, 0xb91f1976}, 

/**/            pi0 = {0x54442D18, 0x400921FB }, /* PI                     */
/**/            pi1 = {0x33145C07, 0x3CA1A626 }, 
/**/            pi2 = {0xb7ed8fbc, 0xb92f1976},

/**/            mp1 = {0x58000000, 0x3FF921FB },/*  1.5707963407039642      */
/**/            mp2 = {0x3C000000, 0xBE4DDE97 },/* -1.3909067564377153e-08  */
/**/            mp3 = {0x99D747F2, 0xBC8CB3B3 },/* -4.9789962505147994e-17  */
/**/            pp3 = {0x98000000, 0xBC8CB3B3 },/* -4.9789962314799099e-17  */
/**/            pp4 = {0x23e32ed7, 0xbacd747f },/* -1.9034889620193266e-25  */
/**/          hpinv = {0x6DC9C883, 0x3FE45F30 },/*  0.63661977236758138     */
/**/          toint = {0x00000000, 0x43380000 };/*  6755399441055744        */
 
#endif
#endif

