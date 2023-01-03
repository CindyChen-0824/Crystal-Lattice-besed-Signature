#ifndef REJ_UNIFORM_H
#define REJ_UNIFROM_H
#include "../inc/system_para.h"
#include "../inc/deftype.h"
#include "../inc/fips202.h"
#include "../inc/symmetric.h"

#define SHAKE128_INIT shake128_stream_init
#define SHAKE256_INIT shake256_stream_init
#define SHAKE128_SQBLOCKS shake128_squeezeblocks
#define SHAKE256_SQBLOCKS shake256_squeezeblocks


/***************************************************
*Func:rej_uni
* Perform rejection sampling for coefficients in [0,Q-1]
*
* @param[in]:a-poly.a
* @param[in]:len-length of a
* @param[in]:buf-array of random bytes
* @param[in]:buflen-length of buf
***************************************************/
int rej_uni(ssi_t* a, int len, uint8_t* buf, int buflen);

/***************************************************
*Func:rej_eta
* Perform rejection sampling for coefficients in [-eta,eta]
* 
* @param[in]:a-poly.a
* @param[in]:len-length of a
* @param[in]:buf-array of random bytes
* @param[in]:buflen-length of buf
***************************************************/
int rej_eta(ssi_t* a, int len, uint8_t* buf, int buflen);
#endif // !REJ_UNIFORM_H

