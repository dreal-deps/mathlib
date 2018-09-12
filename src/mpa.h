
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
/*  MODULE_NAME: mpa.h                                                  */
/*                                                                      */
/*  FUNCTIONS:                                                          */
/*               mcr                                                    */
/*               acr                                                    */
/*               cr                                                     */
/*               cpy                                                    */
/*               cpymn                                                  */
/*               mp_dbl                                                 */
/*               dbl_mp                                                 */
/*               add                                                    */
/*               sub                                                    */
/*               mul                                                    */
/*               inv                                                    */
/*               dvd                                                    */
/*                                                                      */
/* Arithmetic functions for multiple precision numbers.                 */
/* Common types and definition                                          */
/************************************************************************/


typedef struct {/* This structure holds the details of a multi-precision     */
  int e;        /* floating point number, x: d[0] holds its sign (-1,0 or 1) */
  double d[40]; /* e holds its exponent (...,-2,-1,0,1,2,...) and            */
} mp_no;        /* d[1]...d[p] hold its mantissa digits. The value of x is,  */
                /* x = d[1]*r**(e-1) + d[2]*r**(e-2) + ... + d[p]*r**(e-p).  */
                /* Here   r = 2**24,   0 <= d[i] < r  and  1 <= p <= 32.     */
                /* p is a global variable. A multi-precision number is       */
                /* always normalized. Namely, d[1] > 0. An exception is      */
                /* a zero which is characterized by d[0] = 0. The terms      */
                /* d[p+1], d[p+2], ... of a none zero number have no         */
                /* significance and so are the terms e, d[1],d[2],...        */
                /* of a zero.                                                */

typedef union { int i[2]; double d; } number;

#define  X   x->d
#define  Y   y->d
#define  Z   z->d
#define  EX  x->e
#define  EY  y->e
#define  EZ  z->e

#define MAX(x,y) ((x) < (y) ?  (y) : (x))
#define MIN(x,y) ((x) < (y) ?  (x) : (y))

int acr(const mp_no *, const mp_no *, int);
int  cr(const mp_no *, const mp_no *, int);
void cpy(const mp_no *, mp_no *, int);
void cpymn(const mp_no *, int, mp_no *, int);
void mp_dbl(const mp_no *, double *, int);
void dbl_mp(double, mp_no *, int);
void add(const mp_no *, const mp_no *, mp_no *, int);
void sub(const mp_no *, const mp_no *, mp_no *, int);
void mul(const mp_no *, const mp_no *, mp_no *, int);
void inv(const mp_no *, mp_no *, int);
void dvd(const mp_no *, const mp_no *, mp_no *, int);

