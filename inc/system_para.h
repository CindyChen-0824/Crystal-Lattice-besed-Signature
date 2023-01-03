#ifndef SYSTEM_PARA_H
#define SYSTEM_PARA_H

#include "../inc/fips202.h"

//DILITHIUM_VERSION 2
//System parameters & Useful constants

#define Q 8380417
#define QINV 58728449 //Q^(-1) mod 2^32
#define QBITS 23
#define QBTMASK 0x7FFFFF
#define D 13
#define TAU 39
#define GAMMA1 (1<<17)
#define GAMMA2 ((Q-1)/88)
#define K 4
#define L 4
#define ETA 2
#define BETA 78
#define OMEGA 80
#define ROOT 1753
#define N 256
#define MONTFCT 4193792 //2^32 mod Q->-4186625
#define NORMLIM ((Q-1)/8)

#define SEEDBYTES 32
#define CRHBYTES 48
#define RANDLIM (1<<20)

#define W1_PACKSIZE 192
#define Z_PACKSIZE 576
#define T0_PACKSIZE 416
#define T1_PACKSIZE 320
#define S_PACKSIZE 96

#define PK_SIZE (SEEDBYTES + K*T1_PACKSIZE)//32+320k
#define SK_SIZE (2*SEEDBYTES + CRHBYTES + (K+L)*S_PACKSIZE + K*T0_PACKSIZE)//3*32+96*(k+L)+416k
#define SIG_SIZE (SEEDBYTES + 4*Z_PACKSIZE + OMEGA + K)//32+4*576+(80+4)

#define UNI_NBLOCKS ((N*3 + SHAKE128_RATE-1)/SHAKE128_RATE)//(768+168-1)/168
#define UNI_ETA_NBLOCKS ((SHAKE256_RATE + SHAKE128_RATE - 1)/SHAKE128_RATE)//(136+168-1)/168=2
#define UNI_GAMMA1_NBLOCKS ((Z_PACKSIZE + SHAKE256_RATE-1)/SHAKE256_RATE)//(576+136-1)/136
#endif // !SYSTEM_PARA_H

