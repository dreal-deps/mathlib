
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
/**********************************************************************/
/*                                                                    */ 
/* MODULE_NAME: ulog2.c                                               */
/*                                                                    */
/*                                                                    */
/* FUNCTIONS:   ulog2                                                 */
/*              logg2    -   internal routine                         */
/*                                                                    */
/* FILES NEEDED: endian.h mydefs.h ulog2.h upow.h upow.tbl dla.h      */ 
/*               mpa.h mpa2.h mpa.c mplog.h mplog.c mpexp.h mpexp.c   */
/*               slowlog2.c                                           */ 
/*                                                                    */
/* Routine computes cot() - the "ultimate" cotangent                  */
/**********************************************************************/


#include "endian.h"
#include "upow.h"
#include "dla.h"
#include "mydefs.h"
#include "upow.tbl"
#include "ulog2.h" 


double slowlog2(double x, double y); 
double logg2(double x); 

double ulog2(double x) {
int i,j,m,n;
double uu,vv,eps,nx,e,e1,e2,t,t1,t2,res,res1,cor,add=0;
double delta,error;
mynumber u,v,two52={0,0};

u.x = x;
two52.i[HIGH_HALF] = 0x43300000; 
m = u.i[HIGH_HALF];
if (m >= 0  && m < 0x7ff00000)        /* 0 < x < infinity     */ 
 {
  if (m < 0x00100000)             /*  x < 2**-1022   */
    { 
      if (x == 0) {u.i[HIGH_HALF] = 0x80000000;  return 1.0/u.x;  } 
      else {x = x*t53.x; add = -53.0; u.x = x; m = u.i[HIGH_HALF];} 
    }
  
  if ((m&0x000fffff) < 0x0006a09e)
    {u.i[HIGH_HALF] = (m&0x000fffff)|0x3ff00000; two52.i[LOW_HALF]=(m>>20); }
  else
    {u.i[HIGH_HALF] = (m&0x000fffff)|0x3fe00000; two52.i[LOW_HALF]=(m>>20)+1; }
  
  v.x = u.x + bigu.x;
  uu = v.x - bigu.x;
  i = (v.i[LOW_HALF]&0x000003ff)<<2;
  if (two52.i[LOW_HALF] == 1023)         /* nx = 0              */
  {
      if (i > 1192 && i < 1208)          /* |x-1| < 1.5*2**-10  */
      {
	  t = x - 1.0;
	  t1 = (t+5.0e6)-5.0e6;
	  t2 = t-t1;
       	  error = 1.5e-21*ABS(t);
	  e1 = t - 0.5*t1*t1;
	  e2 = t*t*t*(r3+t*(r4+t*(r5+t*(r6+t*(r7+t*r8)))))-0.5*t2*(t+t1);
	  t = e1+e2;
          res1 = t*134217729.0;
          res = res1+t;
          res = res - res1;
          delta = (e1-res)+e2;
          res1 = res*lg2e1.x; 
          delta = res*lg2e2.x+delta*log2e1.x; 
          res = res1+delta; 
          delta = (res1-res)+delta; 
          res1 = res + ((delta>0)?delta+error:delta-error);
          if (res == res1)   return res;
           else return logg2(x); 
      }                  /* |x-1| < 1.5*2**-10  */
      else
      {
	  v.x = u.x*(ui.x[i]+ui.x[i+1])+bigv.x;
	  vv = v.x-bigv.x;
	  j = v.i[LOW_HALF]&0x0007ffff;
	  j = j+j+j;
	  eps = u.x - uu*vv;
	  e1 = eps*ui.x[i];
	  e2 = eps*(ui.x[i+1]+vj.x[j]*(ui.x[i]+ui.x[i+1]));
	  e = e1+e2;
	  e2 =  ((e1-e)+e2);
	  t=ui.x[i+2]+vj.x[j+1];
	  t1 = t+e;
	  t2 = (((t-t1)+e)+(ui.x[i+3]+vj.x[j+2]))+e2+e*e*(p2+e*(p3+e*p4));
	  t=t1+t2;
	  error = 1.5e-24;
          res1 = t*134217729.0;
          res = res1+t;
          res = res - res1;
          delta = (t1-res)+t2;
          res1 = res*lg2e1.x; 
          delta = res*lg2e2.x+delta*log2e1.x; 
          res = res1+delta; 
          delta = (res1-res)+delta; 
          res1 = res + ((delta>0)?delta+error:delta-error);
          if (res == res1)   return res;
           else return logg2(x);
      }
  }   /* nx = 0 */
  else                            /* nx != 0   */
  {
      eps = u.x - uu;
      nx = (two52.x - two52e.x)+add;
      e1 = eps*ui.x[i];
      e2 = eps*ui.x[i+1];
      e=e1+e2;
      e2 = (e1-e)+e2;
      t=nx*ln2a.x+ui.x[i+2];
      t1=t+e;
      t2=(((t-t1)+e)+nx*ln2b.x+ui.x[i+3]+e2)+e*e*(q2+e*(q3+e*(q4+e*(q5+e*q6))));
      t = t1+t2;
      error = 1.5e-21;
      res1 = t*134217729.0;
      res = res1+t;
      res = res - res1;
      delta = (t1-res)+t2;
      res1 = res*lg2e1.x; 
      delta = res*lg2e2.x+delta*log2e1.x; 
      res = res1+delta; 
      delta = (res1-res)+delta; 
      res1 = res + ((delta>0)?delta+error:delta-error);
      if (res == res1)   return res;
         else return logg2(x);    
    }                              /* nx != 0   */
  }              /*  0 < x < infinity   */
else               
  {
   n = m&0x7fffffff;
   if ((n > 0x7ff00000) || (n == 0x7ff00000 && u.i[LOW_HALF] != 0)) return x; 
     /*   x is NaN,  return x itself             */
   else if (x < 0) {u.i[HIGH_HALF] = u.i[LOW_HALF] = -1;  return u.x + u.x; } 
     /* x is negative;  return NaN and cause exception  (NaN + NaN)    */
   else if (x == 0)  {u.i[HIGH_HALF] = 0x80000000;  return 1.0/u.x; } 
    /*  x = +/- 0;  return -infinity and cause zero divide exception    */
   else return x;    /* x = +infinity, so log2(x) = +infinity   */
  }
}

/*
------------------------------------------------------------------------
*/

/* a more accurate but much slower log2 function      */

  double logg2(double x) {
  int i,j,m,n;
  double uu,vv,eps,nx,e,e1,e2,t,t1,t2,res,res1,cor,add=0;
  double ou1,ou2,lu1,lu2,ov,lv1,lv2,a,a1,a2;
  double y,yy,z,zz,j1,j2,j3,j4,j5,j6,j7,j8;
  double delta, error; 
  mynumber u,v,two52={0,0};
  
  u.x = x;
 two52.i[HIGH_HALF] = 0x43300000; 
  m = u.i[HIGH_HALF];
  add=0;
  if (m<0x00100000) {  /* x < 2^-1022 */
    x = x*t53.x;  add = -53.0; u.x = x; m = u.i[HIGH_HALF]; } 
  
  if ((m&0x000fffff) < 0x0006a09e)
    {u.i[HIGH_HALF] = (m&0x000fffff)|0x3ff00000; two52.i[LOW_HALF]=(m>>20); }
  else
    {u.i[HIGH_HALF] = (m&0x000fffff)|0x3fe00000; two52.i[LOW_HALF]=(m>>20)+1; }
  
  v.x = u.x + bigu.x;
  uu = v.x - bigu.x;
  i = (v.i[LOW_HALF]&0x000003ff)<<2;
  /*------------------------------------- |x-1| < 2**-11-------------------------------  */
  if ((two52.i[LOW_HALF] == 1023)  && (i == 1200))
  { 
      t = x - 1.0;
      EMULV(t,s3,y,yy,j1,j2,j3,j4,j5);
      ADD2(-0.5,0,y,yy,z,zz,j1,j2);
      MUL2(t,0,z,zz,y,yy,j1,j2,j3,j4,j5,j6,j7,j8);
      MUL2(t,0,y,yy,z,zz,j1,j2,j3,j4,j5,j6,j7,j8);
      
      e1 = t+z;
      e2 = (((t-e1)+z)+zz)+t*t*t*(ss3+t*(s4+t*(s5+t*(s6+t*(s7+t*s8)))));
      res = e1+e2;
      error = 1.5e-25*ABS(t);
      delta = (e1-res)+e2;
      MUL2(res,delta,log2e1.x,log2e2.x,z,zz,j1,j2,j3,j4,j5,j6,j7,j8);
      res = z+zz;
      delta = (z-res)+zz;
      res1 = res + ((delta>0)?delta+error:delta-error);
      if (res == res1)   return res;
       else return slowlog2(x,res*ln2.x); 
  }
  /*----------------------------- |x-1| > 2**-11  --------------------------  */
  else
  {          /*Computing log(x) according to log table                        */
      nx = (two52.x - two52e.x)+add;
      ou1 = ui.x[i];
      ou2 = ui.x[i+1];
      lu1 = ui.x[i+2];
      lu2 = ui.x[i+3];
      v.x = u.x*(ou1+ou2)+bigv.x;
      vv = v.x-bigv.x;
      j = v.i[LOW_HALF]&0x0007ffff;
      j = j+j+j;
      eps = u.x - uu*vv;
      ov  = vj.x[j];
      lv1 = vj.x[j+1];
      lv2 = vj.x[j+2];
      a = (ou1+ou2)*(1.0+ov);
      a1 = (a+1.0e10)-1.0e10;
      a2 = a*(1.0-a1*uu*vv);
      e1 = eps*a1;
      e2 = eps*a2;
      e = e1+e2;
      e2 = (e1-e)+e2;
      t=nx*ln2a.x+lu1+lv1;
      t1 = t+e;
      t2 = (((t-t1)+e)+(lu2+lv2+nx*ln2b.x+e2))+e*e*(p2+e*(p3+e*p4));
      res=t1+t2;
      error = 1.5e-27;
      delta = (t1-res)+t2;
      MUL2(res,delta,log2e1.x,log2e2.x,z,zz,j1,j2,j3,j4,j5,j6,j7,j8);
      res = z+zz;
      delta = (z-res)+zz;
      res1 = res + ((delta>0)?delta+error:delta-error);
      if (res == res1)   return res;
        else return slowlog2(x,res*ln2.x);  
  }
}

