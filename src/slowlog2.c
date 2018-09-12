
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
/*  MODULE_NAME:  slowlog2.c                                              */
/*                                                                        */
/*  FUNCTION:  slowlog2                                                   */  
/*                                                                        */
/*  FILES NEEDED:mpa.h mpa2.h mpexp.h mplog.h                             */
/*               mpa.c mpexp.c mplog.c                                    */
/*                                                                        */
/*Converting from double precision to Multi-precision and calculating     */
/* e^x                                                                    */
/**************************************************************************/
#include "mpa.h"

void mplog(mp_no *x, mp_no *y, int p);

/*Converting from double precision to Multi-precision and calculating  e^x */
double slowlog2(double x,double y) {
  double w,z,res;
  int orig,i,p;
  int pis[3] = {6,8,32}; 
  double eps[2] = {3.0e-18, 3.0e-30}; 
  mp_no mpx, mpy, mpz,mpw,mpeps,mpcor; 
  static const mp_no mplog2e = {
  1,           1.0,
         1.0,    7427190.0,    5421103.0,   14776189.0,    1047968.0,
  13777533.0,    1169070.0,   16077242.0,   13808817.0,    1460780.0,
  14263106.0,    6590396.0,    3704814.0,   11153113.0,   11291058.0,
   6220674.0,   14139751.0,   13967731.0,   13375637.0,    2178953.0,
   8347142.0,   10993267.0,    6709189.0,    2696780.0,    3126187.0,
   6567559.0,   11203499.0,    4459542.0,   12416890.0,   15149608.0,
  11239449.0,   15303757.0,          0.0,           0.0,         0.0,
         0.0,          0.0,          0.0,           0.0          
}; 
  if (x == 1.0) return 0; 
  for (i=0;i<3;i++) 
  {
    p = pis[i];
    dbl_mp(x,&mpx,p); /* Convert a double precision number  x               */
                    /* into a multiple precision number mpx with prec. p. */
    dbl_mp(y,&mpw,p); 
    mplog(&mpx, &mpw, p); /* Multi-Precision exponential function */
    mul(&mplog2e,&mpw,&mpy,p); 
    if (i < 2) 
     {
      dbl_mp(eps[i],&mpeps,p);
      mul(&mpeps,&mpy,&mpcor,p);
      add(&mpy,&mpcor,&mpw,p);
      sub(&mpy,&mpcor,&mpz,p);
      mp_dbl(&mpw, &w, p);
      mp_dbl(&mpz, &z, p);
      if (w == z)  break; 
     }
    else 
        mp_dbl(&mpy, &w, p);
  }
      return w;
}

