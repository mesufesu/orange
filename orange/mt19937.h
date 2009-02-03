#ifndef _MT19937_H_
#define _MT19937_H_

void init_genrand(unsigned long s);
void init_by_array(unsigned long init_key[], unsigned long key_length);
unsigned long genrand_int32();
long genrand_int31();
double genrand_real1();
double genrand_real2();
double genrand_real3();
double genrand_res53();

#endif