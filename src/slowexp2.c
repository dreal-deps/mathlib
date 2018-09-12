
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
/**************************************************************************/
/*  MODULE_NAME:slowexp2.c                                                */
/*                                                                        */
/*  FUNCTION: slowexp2                                                    */  
/*                                                                        */
/*  FILES NEEDED: mpa.h mpa2.h mpexp.h                                    */
/*                mpa.c mpexp.c                                           */
/*                                                                        */
/*Converting from double precision to Multi-precision and calculating     */
/* 2**x                                                                   */
/**************************************************************************/
#include "mpa.h"

void mpexp(mp_no *x, mp_no *y, int p);

/*Converting from double precision to Multi-precision and calculating  e^x */
double slowexp2(double x) {
  double y,w,z,res,eps=3.0e-18;
  int orig,i,p;
  mp_no mpx, mpy, mpz,mpw,mpeps,mpcor; 
  static const mp_no mpln2 = {
    0,           1.0, 
 11629079.0,    16241103.0,     7973833.0,    14922648.0,      258806.0,
 11485427.0,     4400754.0,    10008109.0,     9047319.0,     5999530.0,
 16395239.0,    12088864.0,     7203756.0,     9983381.0,     5438282.0,
 16390928.0,    15543982.0,     3522872.0,     2180135.0,     5716777.0,
  1141176.0,     2440854.0,    13243938.0,     4909253.0,     1756122.0,
  1126780.0,     3702457.0,    15375301.0,     6707936.0,     7462205.0,
 16693366.0,     4710232.0,           0.0,           0.0,           0.0,
        0.0,           0.0,           0.0,           0.0          
}; 
  if ((x <2.0e-16)&&(x>-2.0e-16)) return 1.0; 
  p=6;
  dbl_mp(x,&mpy,p); /* Convert a double precision number  x               */
                    /* into a multiple precision number mpx with prec. p. */
  mul(&mpln2,&mpy,&mpx,p); 
  mpexp(&mpx, &mpy, p); /* Multi-Precision exponential function */
  dbl_mp(eps,&mpeps,p);
  mul(&mpeps,&mpy,&mpcor,p);
  add(&mpy,&mpcor,&mpw,p);
  sub(&mpy,&mpcor,&mpz,p);
  mp_dbl(&mpw, &w, p);
  mp_dbl(&mpz, &z, p);
  if (w == z)  return w; 
 else {
 p = 8;
 eps *= 1.0e-12;
 dbl_mp(x,&mpy,p); /* Convert a double precision number  x               */
                    /* into a multiple precision number mpx with prec. p. */
  mul(&mpln2,&mpy,&mpx,p); 
  mpexp(&mpx, &mpy, p); /* Multi-Precision exponential function */
  dbl_mp(eps,&mpeps,p);
  mul(&mpeps,&mpy,&mpcor,p);
  add(&mpy,&mpcor,&mpw,p);
  sub(&mpy,&mpcor,&mpz,p);
  mp_dbl(&mpw, &w, p);
  mp_dbl(&mpz, &z, p);
  if (w == z)  return w; 
  else  {                   /* if calculating is not exactly   */
    p = 32;
    dbl_mp(x,&mpy,p);
    mul(&mpln2,&mpy,&mpx,p); 
    mpexp(&mpx, &mpy, p);
    mp_dbl(&mpy, &res, p);
    return res;
  }
 }
}

