
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
/* MODULE_NAME: slowcot.c                                           */
/*                                                                  */
/*                                                                  */
/* FUNCTIONS:   slowcot                                             */
/*              cotMp     internal - multi-precision cotangent      */  
/*                                                                  */
/* FILES NEEDED: endian.h mydefs.h dla.h mpa.h mpa2.h trigo.h       */
/*               branred.h branred.c dosincos.h dosincos.c          */
/*               sincos32.h sincos32.c mptan.c sincos.tbl           */
/*                                                                  */
/* Routine computes cot() - the "ultimate" cotangent  using         */ 
/*        a very accurate but slow algorithm                        */
/********************************************************************/


#include "endian.h"
#include "mydefs.h"
#include "dla.h" 
#include "trigo.h"
#include "mpa.h"

double dubsin(double, double, double *); 
double dubcos(double, double, double *); 
int branred(double, double *, double *); 
void mptan(double x,mp_no *y, int p);
double cotMp(double x); 

double slowcot(double z, double *dd) 
{
double t1,t2,t3,t4,t5,t6,t7,t8,t9,t10, ss[2],cc[2], a,da,q,qq, t,tt,xn,cor;
double x,xx,r,rr;
double abserr,r1,r2; 
mynumber u,v; 
int n;
x = (z<0)?-z:z;
if (x<0.5*hp0.x)       
  {
   abserr = 0;
   dubsin(x,0,ss); 
   dubcos(x,0,cc);                        
  }
 else if (x<1.5*hp0.x)
  {
   abserr = 1.0e-47;
   xx = hp0.x-x;  
   r = xx + hp1.x;
   rr = ((xx - r) + hp1.x)+hp2.x;
   if ((r+rr) >= 0) 
    {
      dubsin(r,rr,cc); 
      dubcos(r,rr,ss);
    }
   else
    {
      dubsin(-r,-rr,cc); 
      dubcos(-r,-rr,ss);
      cc[0] = -cc[0];
      cc[1] = -cc[1]; 
    }
   }
 else if (x<2.5*hp0.x)
  {
   abserr = 1.0e-47; 
   xx = x-pi0.x;  
   r = xx - pi1.x;
   rr = ((xx - r) - pi1.x) - pi2.x;
   if ((r+rr) >= 0) 
    {
      dubsin(r,rr,ss); 
      dubcos(r,rr,cc);
    }
   else
    {
      dubsin(-r,-rr,ss); 
      dubcos(-r,-rr,cc);
      ss[0] = -ss[0];
      ss[1] = -ss[1]; 
    }
   }
else if (x < 281474976710656.0)  /*  |x| < 2**48          */ 
   {
     abserr = 1.0e-46*ABS(x); 
     t = (x*hpinv.x + toint.x);
     xn = t - toint.x;
     v.x = t;
     EMULV(xn,hp0.x,a,da,t1,t2,t3,t4,t5)
     n =v.i[LOW_HALF]&1;
     a = (x-a)-da;
     MUL2(xn,0,hp1.x,hp2.x,q,qq,t1,t2,t3,t4,t5,t6,t7,t8)
     t = a-q;
     tt = ((a-t)-q) - qq;
     a = t+tt;
     da = (t-a)+tt; 
     if (n==0) 
        {
         if (a<0) 
          {
            dubsin(-a,-da,ss);
            dubcos(-a,-da,cc);
            ss[0] = -ss[0];
            ss[1] = -ss[1]; 
          }
        else 
          {
            dubsin(a,da,ss);
            dubcos(a,da,cc);
          }
        }
      else
       {
         if (a<0) 
          {
            dubsin(-a,-da,cc);
            dubcos(-a,-da,ss);
          }
        else 
          {
            dubsin(a,da,cc);
            dubcos(a,da,ss);
            ss[0] = -ss[0];
            ss[1] = -ss[1]; 
          }
        }
   }
else  
   {
     abserr = 1.1e-24;
     n = branred(x,&a,&da);
     n &= 1;
     if (n==0) 
        {
         if (a<0) 
          {
            dubsin(-a,-da,ss);
            dubcos(-a,-da,cc);
            ss[0] = -ss[0];
            ss[1] = -ss[1]; 
          }
        else 
          {
            dubsin(a,da,ss);
            dubcos(a,da,cc);
          }
        }
      else
       {
         if (a<0) 
          {
            dubsin(-a,-da,cc);
            dubcos(-a,-da,ss);
          }
        else 
          {
            dubsin(a,da,cc);
            dubcos(a,da,ss);
            ss[0] = -ss[0];
            ss[1] = -ss[1]; 
          }
        }
   }
DIV2(cc[0],cc[1],ss[0],ss[1],r,rr,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10);
r1 = r + (1.0000001*rr+abserr);
r2 = r + (1.0000001*rr-abserr);
if ((r != r1) || (r != r2)) return cotMp(z);
else return (z<0)?-r:r;
}

double cotMp(double x)
{
mynumber u;
  int p;
  double y;
  mp_no mpy,mpz;
u.x = x;
  p=32;  
  mptan(x, &mpy, p);
  inv(&mpy,&mpz,p);
  mp_dbl(&mpz,&y,p);  
  return y;
}
