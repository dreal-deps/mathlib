#define  BIG_ENDI
#undef   LITTLE_ENDI

#ifdef BIG_ENDI
#define HIGH_HALF 0
#define  LOW_HALF 1
#else 
#ifdef LITTLE_ENDI
#define HIGH_HALF 1
#define  LOW_HALF 0
#endif
#endif

#define ABS(x)   ((x) <  0  ? -(x) : (x))
