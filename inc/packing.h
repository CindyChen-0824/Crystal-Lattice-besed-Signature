#ifndef PACKING_H
#define PACKING_H

#include "../inc/deftype.h"
#include "../inc/system_para.h"
#include "../inc/polyvct.h"

/************************************
*Func:bit_packing_w1
* 
* Implementation for Bit-packing w1
* 
* @param[in]:a-Poly.a to be packed
* @param[out]:r-the result
************************************/
void bit_packing_w1(uint8_t* r, poly* a);

/************************************
*Func:bit_packing_z
*
* Implementation for Bit-packing z
*
* @param[in]:a-Poly.a to be packed
* @param[out]:r-the result
************************************/
void bit_packing_z(uint8_t* r, poly* a);

/************************************
*Func:bit_unpacking_z
*
* Implementation for Bit-unpacking z
*
* @param[in]:a-to be unpacked
* @param[out]:r-the result Poly.r
************************************/
void bit_unpacking_z(poly* r, uint8_t* a);

/***********************************
*Func:bit_packing_t0
* 
* Implementation for Bit-packing t0
*
* @param[in]:a-Poly.a to be packed
* @param[out]:r-the result
***********************************/
void bit_packing_t0(uint8_t* r, poly* a);

/************************************
*Func:bit_unpacking_t0
*
* Implementation for Bit-unpacking t0
*
* @param[in]:a-to be unpacked
* @param[out]:r-the result Poly.r
************************************/
void bit_unpacking_t0(poly* r, uint8_t* a);

/***********************************
*Func:bit_packing_t1
*
* Implementation for Bit-packing t1
*
* @param[in]:a-Poly.a to be packed
* @param[out]:r-the result
***********************************/
void bit_packing_t1(uint8_t* r, poly* a);

/************************************
*Func:bit_unpacking_t1
*
* Implementation for Bit-unpacking t1
*
* @param[in]:a-to be unpacked
* @param[out]:r-the result Poly.r
************************************/
void bit_unpacking_t1(poly* r, uint8_t* a);

/***********************************
*Func:bit_packing_s
*
* Implementation for Bit-packing s
*
* @param[in]:a-Poly.a to be packed
* @param[out]:r-the result
***********************************/
void bit_packing_s(uint8_t* r, poly* a);

/************************************
*Func:bit_unpacking_s
*
* Implementation for Bit-unpacking s
*
* @param[in]:a-to be unpacked
* @param[out]:r-the result Poly.r
************************************/
void bit_unpacking_s(poly* r, uint8_t* a);

/**************************************
*Func:pk_packing
* 
* Packing the public key:pk(rho||t1)
* 
* @param[out]:pk-public key
* @param[in]:rho
* @param[in]:t1
**************************************/
void pk_packing(uint8_t pk[PK_SIZE], const uint8_t rho[SEEDBYTES], polyvctk* t1);

/**************************************
*Func:pk_unpacking
*
* Unpacking the public key:pk(rho||t1)->rho,t1
*
* @param[in]:pk-public key
* @param[out]:rho
* @param[out]:t1
**************************************/
void pk_unpacking(uint8_t rho[SEEDBYTES], polyvctk* t1, const uint8_t* pk);

/**********************************************
*Func:sk_packing
* 
* Packing the secrete key:sk(rho,K,tr,s1,s2,t0)
* 
* @param[out]:sk-secrete key
* @param[in]:rho
* @param[in]:key
* @param[in]:tr
* @param[in]:s1
* @param[in]:s2
* @param[in]:t0
***********************************************/
void sk_packing(uint8_t* sk, const uint8_t rho[SEEDBYTES], uint8_t key[SEEDBYTES], uint8_t tr[CRHBYTES], polyvctl* s1, polyvctk* s2, polyvctk* t0);

/**********************************************
*Func:sk_unpacking
*
* Unpacking the secrete key:sk(rho,K,tr,s1,s2,t0)
*
* @param[in]:sk-secrete key
* @param[out]:rho
* @param[out]:key
* @param[out]:tr
* @param[out]:s1
* @param[out]:s2
* @param[out]:t0
***********************************************/
void sk_unpacking(uint8_t rho[SEEDBYTES], uint8_t key[SEEDBYTES], uint8_t tr[CRHBYTES], polyvctl* s1, polyvctk* s2, polyvctk* t0, const uint8_t* sk);

/**********************************************
*Func:sig_packing
* 
* Packing the signature
* 
* @param[in]:z
* @param[in]:h
* @param[in]:c
* @param[out]:sig-signature
***********************************************/
void sig_packing(uint8_t sig[SIG_SIZE], const polyvctl* z, const polyvctk* h, const uint8_t c[SEEDBYTES]);

/**********************************************
*Func:sig_unpacking
*
* Unpacking the signature
*
* @param[out]:z
* @param[out]:h
* @param[out]:c
* @param[in]:sig-signature
***********************************************/
int sig_unpacking(polyvctl* z, polyvctk* h, uint8_t c[SEEDBYTES], const uint8_t sig[SIG_SIZE]);
#endif // !PACKING_H

