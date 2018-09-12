
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
/* FUNCTIONS:   ucot                                                */
/*              cotpol   -   internal routine                       */
/*              cottab   -   internal routine                       */
/*              tanpol   -   internal routine                       */
/*                                                                  */
/* FILES NEEDED: endian.h mydefs.h dla.h mpa.h mpa2.h trigo.h       */
/*               branred.h branred.c dosincos.h dosincos.c          */
/*               sincos32.h sincos32.c mptan.c slowcot.c            */
/*               ucot.h ucot.tbl sincos.tbl                         */
/*                                                                  */
/* Routine computes cot() - the "ultimate" cotangent                */
/********************************************************************/



#include "endian.h"
#include "mydefs.h"
#include "ucot.h"
#include "ucot.tbl"
#include "trigo.h"

int branred(double,double *,double *);
double slowcot(double);
double cotpol(double orig, double xx, double dx, double abserr, int neg);
double cottab(double orig, double xx, double dx, double abserr, int neg);
double tanpol(double orig, double xx, double dx, double abserr, int neg);

static const double cuteps = 3.0e6;          /*  something like 1.5*2**21   */
static const double tanbig = 2.0e11;         /*  something like 1.5*2**37   */
static const double err1 = 1.00040,  err2 = 1.0030, err3 = 1.007;


double ucot(double x)
{
double x1,x2,y,y1,y2,xx,dx,z,t,tt,r,rr,eps,eps1,eps2,epss,e2,tfac,xn,a,da,xn1,xn2;
mynumber u,v,w;
int i,m,mm,n;
w.x = x;
m = w.i[HIGH_HALF]&0x7fffffff;
mm = w.i[HIGH_HALF];
if (m < 0x3C800000)  return 1.0/x;       /* |x| < 2**-54;  cot(x) = 1/x, even if x = 0  */
else if (m < 0x3FCF4BC7)    /* |x| < 0.2445      */
  {
    y = 1.0/x;
    u.x = x;
    u.i[LOW_HALF] = 0;
    x1 = u.x;
    x2 = x -x1;
    v.x = y;
    xx = x*x;
    v.i[LOW_HALF] = 0;
    z = ((((((c13.x*xx +c11.x)*xx +c9.x)*xx +c7.x)*xx + c5.x)*xx +c3.x)*xx + cc1.x)*x +c1.x*x2;
    y1 = v.x;
    y2 = y*((1.0 -x1*y1) -x2*y1);
    t = x1*c1.x;
    y2 += z;
    r = y1 + (t + y2);
    rr = ((y1 - r) + t) + y2;
    if (r == r + err1*rr) return r;
    else
      {
       y1 = r+rr;
       y2 = (r-y1)+rr;
       if (y1 == y1 + err1*y2) return y1;
       else return slowcot(x);
      }
  }     /*  x < 0.2445;  cot(x) > 4.0      */
else if (m < 0x3FF53334)      /* |x} <= 1.325   */
  {
    xx = (mm<0)?-x:x;
    y = xx + bigtab.x;
    v.x = y;
    eps = xx - (y-bigtab.x);
    i = (v.i[LOW_HALF])<<2;
    eps1 = (eps + cuteps)-cuteps;
    e2 = eps*eps;
    eps2 = eps - eps1;
    tfac = ctg.x[i+2]+ctg.x[i+3];
    t = eps*e2*((st7.x*e2 + st5.x)*e2 +st3.x)+eps2;
    r = ctg.x[i];
    rr = eps1*ctg.x[i+2];
    tt = t+eps1;
    t = tfac*(t - r*tt*tt/(1.0+r*tt)) + (eps1*ctg.x[i+3] - ctg.x[i+1]);
    y1 = r - (rr+t);
    y2 = ((r-y1) - rr) - t;
    if (y1 == y1 + err2*y2) return (mm<0)?-y1:y1;
    else
      {
       r = y1 + y2;
       rr = (y1-r)+y2;
       if (r == r + err2*rr) return (mm<0)?-r:r;
       else return slowcot(x);
      }
  }
else if (m < 0x3FFD10C3)          /*   |x| < Pi - 1.325      */
  {
   xx = (mm<0)?-x:x;
   y = hp0.x -xx;
   y1 = y + hp1.x;
   y2 = ((y-y1)+hp1.x)+hp2.x;
   x1 = (y1 + tanbig) - tanbig;
   xx = y1*y1;
   x2 = (y1-x1)+y2;
   z = y1*xx*xx*(((((((mt19.x*xx+mt17.x)*xx+mt15.x)*xx+mt13.x)*xx+mt11.x)*xx+mt9.x)*xx+mt7.x)*xx+mt5.x);
   r = a1.x*x1*x1*x1;
   rr = a1.x*x2*(xx+x1*y1+x1*x1)+a2.x*y1*xx;
   y = y1+r;
   rr = ((((y1-y)+r)+y2)+rr)+z;
   r = y+rr;
   rr = (y-r)+rr;
   if  (r == r + err3*rr) return (mm<0)?-r:r;
   else return slowcot(x);
  }
else if (m < 0x40072A98)      /* |x} <= Pi - 0.2445   */
  {
    x1 = (mm<0)?pi0.x+x:pi0.x-x;
    xx = x1 + pi1.x;
    dx = ((x1-xx)+pi1.x)+pi2.x;
    y = xx + bigtab.x;
    v.x = y;
    eps = xx - (y-bigtab.x);
    epss = eps+dx;
    i = (v.i[LOW_HALF])<<2;
    eps1 = (eps + cuteps)-cuteps;
    e2 = epss*epss;
    eps2 = (eps - eps1)+dx;
    tfac = ctg.x[i+2]+ctg.x[i+3];
    t = epss*e2*((st7.x*e2 + st5.x)*e2 +st3.x)+eps2;
    r = ctg.x[i];
    rr = eps1*ctg.x[i+2];
    tt = t+eps1;
    t = tfac*(t - r*tt*tt/(1.0+r*tt)) + (eps1*ctg.x[i+3] - ctg.x[i+1]);
    y1 = r - (rr+t);
    y2 = ((r-y1) - rr) - t;
    if (y1 == y1 + err2*y2) return (mm<0)?y1:-y1;
    else
      {
       r = y1 + y2;
       rr = (y1-r)+y2;
       if (r == r + err2*rr) return (mm<0)?r:-r;
       else return slowcot(x);
      }
  }
else if (m < 0x400B16B8)    /* |x| < Pi + 0.2445      */
  {
    x1 = (mm<0)?pi0.x+x:pi0.x-x;
    xx = x1 + pi1.x;
    dx = ((x1-xx)+pi1.x)+pi2.x;
    y = 1.0/xx;
    u.x = xx;
    u.i[LOW_HALF] = 0;
    x1 = u.x;
    x2 = (xx -x1)+dx;
    v.x = y;
    tt = xx*xx;
    v.i[LOW_HALF] = 0;
    z = ((((((c13.x*tt +c11.x)*tt +c9.x)*tt +c7.x)*tt + c5.x)*tt +c3.x)*tt + cc1.x)*xx +(3.0*tt*dx*c3.x+c1.x*x2);
    y1 = v.x;
    y2 = y*((1.0 -x1*y1) -x2*y1);
    t = x1*c1.x;
    y2 += z;
    r = y1 + (t + y2);
    rr = ((y1 - r) + t) + y2;
    if (r == r + err1*rr) return (mm<0)?r:-r;
    else
      {
       y1 = r+rr;
       y2 = (r-y1)+rr;
       if (y1 == y1 + err1*y2) return (mm<0)?y1:-y1;
       else return slowcot(x);
      }
  }
else if (m < 0x419921FB )  /*  |x| < (Pi/2)*2**26          */
  {
    t = (x*hpinv.x + toint.x);
    xn = t - toint.x;
    v.x = t;
    y = (x - xn*mp1.x) - xn*mp2.x;
    n =v.i[LOW_HALF]&1;
    da = xn*mp3.x;
    a=y-da;
    da = (y-a)-da;
    eps = ABS(x)*1.0e-30;
    xx = ABS(a);

     switch (n)
    {
     case 0:
     if (xx < 0.2445) return cotpol(x,a,da,eps,0);
     else return (a<0)?cottab(x,xx,-da,eps,1):cottab(x,a,da,eps,0);
     break;

     case 1:
     if (xx < 0.2466) return tanpol(x,a,da,eps,1);
     else
       {
         if (a>0) {y1 = hp0.x-a; y2 = ((hp0.x -y1)-a) +(hp1.x-da); i = 1;}
         else {y1 = hp0.x+a;  y2 = ((hp0.x-y1)+a)+(hp1.x+da); i = 0;}
         return cottab(x,y1,y2,eps,i);
       }
     break;

     default:
     return 0;     /*  will never happen   */
     break;
   }
  }
else if (m < 0x42F00000 )  /*  |x| < 2**48          */
  {
    t = (x*hpinv.x + toint.x);
    xn = t - toint.x;
    v.x = t;
    xn1 = (xn+8.0e22)-8.0e22;
    xn2 = xn - xn1;
    y = ((((x - xn1*mp1.x) - xn1*mp2.x)-xn2*mp1.x)-xn2*mp2.x);
    n =v.i[LOW_HALF]&1;
    da = xn1*pp3.x;
    t=y-da;
    da = (y-t)-da;
    da = (da - xn2*pp3.x) -xn*pp4.x;
    a = t+da;
    xx = ABS(a);
    da = (t-a)+da;
    eps = 1.0e-24;

    switch (n)
    {
     case 0:
     if (xx < 0.2445) return cotpol(x,a,da,eps,0);
     else return (a<0)?cottab(x,xx,-da,eps,1):cottab(x,a,da,eps,0);
     break;

     case 1:
     if (xx < 0.2466) return tanpol(x,a,da,eps,1);
     else
       {
         if (a>0) {y1 = hp0.x-a; y2 = ((hp0.x -y1)-a) +(hp1.x-da); i = 1;}
         else {y1 = hp0.x+a;  y2 = ((hp0.x-y1)+a)+(hp1.x+da); i = 0;}
         return cottab(x,y1,y2,eps,i);
       }
     break;

     default:
     return 0;     /*  will never happen   */
     break;
   }
  }
else if (m < 0x7FF00000 )  /*  |x| < infinity       */
  {
    n = branred(x,&a,&da);
    eps = 1.1e-24;
    n &= 1;
    xx = ABS(a);

    switch (n)
    {
     case 0:
     if (xx < 0.2445) return cotpol(x,a,da,eps,0);
     else return (a<0)?cottab(x,xx,-da,eps,1):cottab(x,a,da,eps,0);
     break;

     case 1:
     if (xx < 0.2466) return tanpol(x,a,da,eps,1);
     else
       {
         if (a>0) {y1 = hp0.x-a; y2 = ((hp0.x -y1)-a) +(hp1.x-da); i = 1;}
         else {y1 = hp0.x+a;  y2 = ((hp0.x-y1)+a)+(hp1.x+da); i = 0;}
         return cottab(x,y1,y2,eps,i);
       }
     break;

     default:
     return 0;     /*  will never happen   */
     break;
   }
  }
else     /* x is either infinity or NaN  */
  {
   if ((m == 0x7ff00000) && (w.i[LOW_HALF] == 0))
      { w.i[LOW_HALF] = 1;  return w.x; }  /* x is +/- infinity, return NaN   */
   else return x;    /* x is NaN,  return x itself   */
  }
  return 0.0; /* Never reached (makes the compiler happy)
                 Dummy return stmt added by FG. */
}

/*
------------------------------------------------------------------------------------------
*/

double cotpol(double orig, double xx, double dx, double abserr, int neg)
{
    double x1,x2,y,y1,y2,t,tt,z,r,rr,rrr;
    mynumber u,v;
    y = 1.0/xx;
    u.x = xx;
    u.i[LOW_HALF] = 0;
    x1 = u.x;
    x2 = (xx -x1)+dx;
    v.x = y;
    tt = xx*xx;
    v.i[LOW_HALF] = 0;
    z = ((((((c13.x*tt +c11.x)*tt +c9.x)*tt +c7.x)*tt + c5.x)*tt +c3.x)*tt + cc1.x)*xx +(3.0*tt*dx*c3.x+c1.x*x2);
    y1 = v.x;
    y2 = y*((1.0 -x1*y1) -x2*y1);
    t = x1*c1.x;
    y2 += z;
    r = y1 + (t + y2);
    rr = ((y1 - r) + t) + y2;
    rrr = (rr>0)?abserr+rr*err1:abserr-rr*err1;
    if (r == r + rrr) return (neg)?-r:r;
    else
      {
       y1 = r+rr;
       y2 = (r-y1)+rr;
       rrr = (y2>0)?abserr+y2*err1:abserr-y2*err1;
       if (y1 == y1 + rrr) return (neg)?-y1:y1;
       else return slowcot(orig);
      }
  }

double cottab(double orig,double xx,double dx, double abserr, int neg)
{
    double y,eps,epss,eps1,eps2,tfac,t,r,rr,tt,y1,y2,e2,rrr;
    int i;
    mynumber u,v;
    y = xx + bigtab.x;
    v.x = y;
    eps = xx - (y-bigtab.x);
    epss = eps+dx;
    i = (v.i[LOW_HALF])<<2;
    eps1 = (eps + cuteps)-cuteps;
    e2 = epss*epss;
    eps2 = (eps - eps1)+dx;
    tfac = ctg.x[i+2]+ctg.x[i+3];
    t = epss*e2*((st7.x*e2 + st5.x)*e2 +st3.x)+eps2;
    r = ctg.x[i];
    rr = eps1*ctg.x[i+2];
    tt = t+eps1;
    t = tfac*(t - r*tt*tt/(1.0+r*tt)) + (eps1*ctg.x[i+3] - ctg.x[i+1]);
    y1 = r - (rr+t);
    y2 = ((r-y1) - rr) - t;
    rrr = (y2>0)?abserr+y2*err2:abserr-y2*err2;
    if (y1 == y1 + rrr) return (neg)?-y1:y1;
    else
      {
       r = y1 + y2;
       rr = (y1-r)+y2;
       rrr = (rr>0)?abserr+rr*err2:abserr-rr*err2;
       if (r == r + rrr) return (neg)?-r:r;
       else return slowcot(orig);
      }
  }

double tanpol(double orig, double y1, double y2, double abserr, int neg)
  {
   double x1,x2,xx,z,r,rr,y,rrr;
   x1 = (y1 + tanbig) - tanbig;
   xx = y1*y1;
   x2 = (y1-x1)+y2;
   z = y1*xx*xx*(((((((mt19.x*xx+mt17.x)*xx+mt15.x)*xx+mt13.x)*xx+mt11.x)*xx+mt9.x)*xx+mt7.x)*xx+mt5.x);
   r = a1.x*x1*x1*x1;
   rr = a1.x*x2*(xx+x1*y1+x1*x1)+a2.x*y1*xx;
   y = y1+r;
   rr = ((((y1-y)+r)+y2)+rr)+z;
   r = y+rr;
   rr = (y-r)+rr;
   rrr = (rr>0)?abserr+rr*err3:abserr-rr*err3;
   if (r == r + rrr) return (neg)?-r:r;
   else return slowcot(orig);
  }
