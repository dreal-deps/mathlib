
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
/********************************************************************/
/*                                                                  */ 
/* MODULE_NAME: ucot.c                                              */
/*                                                                  */
/*                                                                  */
/* FUNCTIONS:   uexp2                                               */
/*                                                                  */
/* FILES NEEDED: endian.h mydefs.h uexp.h uexp.tbl slowexp2.c       */
/*               mpa.h mpa2.h mpa.c  mpexp.h mpexp.c                */
/*                                                                  */
/* Routine computes uexp2() - the "ultimate" 2**x                   */
/********************************************************************/


#include "endian.h"
#include  "uexp.h"
#include "mydefs.h"
#include "uexp.tbl"

double slowexp2(double x); 

double uexp2(double x) 
 {
  double bexp, z, eps, del, base, y, al, bet, res, rem, cor;
  mynumber junk1, junk2, binexp  = {0,0};
  int4 k,i,j,n,ex;
  
  junk1.x = x;
  n = (junk1.i[HIGH_HALF])&hugeint;  
  if ((n<0x408FF000) && (n>0x3C800000) )  /*  2**-55 < |x| < 1022  */
  {
   junk1.x = x + three51.x;
   y = junk1.x - three51.x;  
   y = x - y; 
   z = y*ln2.x; 
   junk2.x = z + three33.x;
   base = junk2.x - three33.x;   
   binexp.i[HIGH_HALF] =(junk1.i[LOW_HALF]+1023)<<20; 
   del = ln2.x*((y - lg2e1.x*base) - lg2e2.x*base); 
   i = ((junk2.i[LOW_HALF]>>8)&0xfffffffe)+356;
   j = (junk2.i[LOW_HALF]&511)<<1;
   eps = del + del*del*(p3.x*del + p2.x);    
   al = coar.x[i]*fine.x[j];
   bet =(coar.x[i]*fine.x[j+1] + coar.x[i+1]*fine.x[j]) + coar.x[i+1]*fine.x[j+1];
   rem=(bet + bet*eps)+al*eps;
   res = al + rem;
   cor = (al - res) + rem;
   if  (res == (res+cor*err_0)) return res*binexp.x; 
   else return slowexp2(x);    /*if error is over bound */
  }
  else 
   {
     if (n <= 0x3C800000) return 1.0;     /*  |x| < 2**-54   */
   else
     if (n >= 0x40910000)        /* x is either NaN or inf or |x| >= 1088  */
       {
        if (n > infint) return x;                   /* x is NaN,  return x itself  */ 
        if (n < infint) return ( (x>0) ? (hhuge*hhuge) : (tiny*tiny) );
        /* x is finite,  cause either overflow or underflow  */
        if (junk1.i[LOW_HALF] != 0)  return x;      /*  x is NaN, return x itself  */
        return ((x>0)?inf.x:zero );             /* |x| = inf;  return either inf or 0 */
      }
  else
     if (x >= 1024.0) return hhuge*hhuge;      /* overflow   */
  else
     if (x>0) return 8.0*uexp2(x-3.0);     /* 2^x = 8.0*2^(x-3)  and (x-3) < 1022   */
  else
     if (x == -1022.0) return tm1022.x;    /* x is exactly -1022   */
  else
     if (x <= -1075.0) return tiny*tiny;   /* x <= -1075;    underflow   */
 else
     /*  -1022 < x < -1075;  gradual underflow  */
    {
      junk1.x = x + three51.x;
      y = junk1.x - three51.x;  
      y = x - y; 
      z = y*ln2.x; 
      junk2.x = z + three33.x;
      base = junk2.x - three33.x;   
      binexp.i[HIGH_HALF] =(junk1.i[LOW_HALF]+1023)<<20; 
      del = ln2.x*((y - lg2e1.x*base) - lg2e2.x*base); 
      i = ((junk2.i[LOW_HALF]>>8)&0xfffffffe)+356;
      j = (junk2.i[LOW_HALF]&511)<<1;
      eps = del + del*del*(p3.x*del + p2.x);    
      al = coar.x[i]*fine.x[j];
      bet =(coar.x[i]*fine.x[j+1] + coar.x[i+1]*fine.x[j]) + coar.x[i+1]*fine.x[j+1];
      rem=(bet + bet*eps)+al*eps;
      res = al + rem;
      cor = (al - res) + rem;

    ex = junk1.i[LOW_HALF];
    if (res < 1.0) {res+=res; cor+=cor; ex-=1;}
    ex = -(1022+ex);
    binexp.i[HIGH_HALF] = (1023-ex)<<20;
    res*=binexp.x;
    cor*=binexp.x;
    eps=1.0000000001+(err_0-1.0)*binexp.x;
    z=1.0+res;
    y = ((1.0-z)+res)+cor;
    res=z+y;
    cor = (z-res)+y;
    if (res == (res + eps*cor)) 
      {
       binexp.i[HIGH_HALF] = 0x00100000;
       return (res-1.0)*binexp.x;
      }
    else return slowexp2(x); /*   if error is over bound    */
 
  }

   }
}
