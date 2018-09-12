#ifdef BIG_ENDI
const static mynumber log2e1    = { 0x3FF71547, 0x652B82FE }; 
const static mynumber log2e2    = { 0x3C7777D0, 0xFFDA0D24 }; 
const static mynumber lg2e1     = { 0x3FF71547, 0x64000000 };  
const static mynumber lg2e2     = { 0x3E32B82F, 0xE1777D10 }; 
const static mynumber ln2      =  { 0x3FE62E42, 0xFEFA39EF };
#else
#ifdef LITTLE_ENDI
 const static mynumber log2e1   = { 0x652B82FE, 0x3FF71547 };
 const static mynumber log2e2   = { 0xFFDA0D24, 0x3C7777D0 }; 
 const static mynumber lg2e1    = { 0x64000000, 0x3FF71547 }; 
 const static mynumber lg2e2    = { 0xE1777D10, 0x3E32B82F };   
 const static mynumber ln2      = { 0xFEFA39EF, 0x3FE62E42 };
#endif
#endif
