#ifndef POLY_H
#define POLY_H

#include "../inc/system_para.h"
#include "../inc/deftype.h"
#include "../inc/rdc.h"

typedef struct {
	ssi_t coff[N];
}poly;

/*Basic Operation*/
/************************************************
*Func:poly_rdc
* 
* Reduce all coefficients of poly. a in range [-6283009,6283007]
* 
* @param[in]:a-poly
************************************************/
void poly_rdc(poly* a);

/***********************************************
* Func:poly_coff_add_q
* 
* For any negative coeddicients of poly.a 
* Add Q to thme.
* 
* @param[in]:a-poly
************************************************/
void poly_coff_add_q(poly* a);

/***********************************************
*Func:poly_add
* 
* Poly Addition:r=a+b
* 
* @param[in]:a-poly a
* @param[in]:b-poly b
* @param[out]:r-poly r, result
************************************************/
void poly_add(poly* r, poly* a, poly* b);

/***********************************************
*Func:poly_sub
*
* Poly Substraction:r=a-b
*
* @param[in]:a-poly a
* @param[in]:b-poly b
* @param[out]:r-poly r, result
************************************************/
void poly_sub(poly* r, poly* a, poly* b);

/***********************************************
*Func:poly_lsh
* 
* Multiply poly.a by 2^13 without reduction.
* Assume all coefficients <=2^18
* 
* @param[in]:a-poly a
* @param[out]:r-poly r
************************************************/
void poly_lsh(poly* r, poly* a);

/***********************************************
*Func:poly_ntt
* 
* Forward ntt for coefficients of poly.a
*
*@param[in]:a-poly a
************************************************/

/*Poly. NTT/INTT*/
void poly_ntt(poly* a);

/***********************************************
*Func:poly_invntt_tomont
*
* Inverse ntt for coefficients of poly.a in Montgomary domain.
*
*@param[in]:a-poly a
************************************************/
void poly_invntt_tomont(poly* a);

/***********************************************
*Func:poly_mul_inmont
* 
* Multiply two poly.s a and b in Montgomary domain.
* 
* @param[in]:a-poly a
* @param[in]:b-poly b
* @param[out]:r-poly r, result
************************************************/
void poly_mul_inmont(poly* r, poly* a, poly* b);

/************************************************
*Func:poly_power2round
* 
* Power2round for poly.a's coefficients
* 
* @param[in]:a-poly a
* @param[out]:a0-poly a0->low bits of coefficients of a
* @param[out]:a1-poly a1->high bits of coefficients of a
************************************************/

/*Poly. Rounding*/
void poly_power2round(poly* a0, poly* a1, poly* a);

/************************************************
*
* Func:poly_decompose
* 
* Decompose for poly.a's coefficients
* 
* @param[in]:a-poly a
* @param[out]:a0-poly a0->low bits of coefficients of a
* @param[out]:a1-poly a1->high bits of coefficients of a
************************************************/
void poly_decompose(poly* a0, poly* a1, poly* a);

/**********************************************************
*Func:poly_makehint
* 
* Compute hint for poly. a.
* Rreturns the summary of hints for each coefficients of a.
* 
* @param[in]:a-poly a
* @param[out]:a0-poly a0->low bits of coefficients of a
* @param[out]:a1-poly a1->high bits of coefficients of a
***********************************************************/
int poly_makehint(poly* a0, poly* a1, poly* a);

/**********************************************************
*Func:poly_highbits
* 
* Returns highbits for poly.a's coefficients
* 
* @param[in]:a-poly a
* @param[out]:a0-poly a0->low bits of coefficients of a
* @param[out]:a1-poly a1->high bits of coefficients of a
***********************************************************/
void poly_highbits(poly* a0, poly* a1, poly* a);

/**********************************************************
*Func:poly_lowbits
*
* Returns lowbits for poly.a's coefficients
*
* @param[in]:a-poly a
* @param[out]:a0-poly a0->low bits of coefficients of a
* @param[out]:a1-poly a1->high bits of coefficients of a
***********************************************************/
void poly_lowbits(poly* a0, poly* a1, poly* a);

/****************************************************
*Func:poly_usehint
* 
* Usehint for poly.a
* Return correct high bits according to hint.
* 
* @param[in]:a-poly a
* @param[out]:a0-poly a0->low bits of coefficients of a
* @param[out]:a1-poly a1->high bits of coefficients of a
* @param[in]:h-hint poly.
* @param[out]:r-poly r
*****************************************************/
void poly_usehint(poly* r, poly* a0, poly* a1, poly* a, poly* h);

/*Poly. Uniform*/
/*********************************************
*Func:poly_checknorm
* 
* Check norm if all are in [-B,B]
* Returns 1 if it is not, else returns 0.
* 
* @param[in]:a-poly a
* @param[in]:B-norm limitation
*********************************************/
int poly_checknorm(poly* a, ssi_t B);

/*********************************************************
*Func:poly_uni
*
* Sampling poly. with uniformly random coefficients
* in [0,Q-1] by rejection sampling.
*
* @param[in]:a-poly a
* @param[in]:seed-byte array with seed of length SEEDBYTES
* @param[in]:nonce-2 bytes
**********************************************************/
void poly_uni(poly* a, uint8_t* seed, ssi_t nonce);

/*********************************************************
*Func:poly_uni_eta
*
* Sampling poly. with uniformly random coefficients
* in [-ETA,ETA] by rejection sampling.
*
* @param[in]:a-poly a
* @param[in]:seed-byte array with seed of length SEEDBYTES
* @param[in]:nonce-2 bytes
**********************************************************/
void poly_uni_eta(poly* a, uint8_t* seed, ssi_t nonce);

/*********************************************************
*Func:poly_uni_gamma1
* 
* Sampling poly. with uniformly random coefficients
* in [-GAMMA1+1,GAMMA1] by rejection sampling.
*
* @param[in]:a-poly a
* @param[in]:seed-byte array with seed of length SEEDBYTES
* @param[in]:nonce-2 bytes
********************************************************/
void poly_uni_gamma1(poly* a, uint8_t* seed, ssi_t nonce);

/*********************************************
*Func:poly_ExpandA
*
* Implementation of ExpandA.
*
* @param[out]:mat-output matrix
* @param[in]:rho-seed rho
********************************************/
//void poly_ExpandA(polyvctl mat[K], uint8_t* rho);

/*********************************************
*Func:poly_SampleInBall
*
* Implementation of SampleInBall
*
* @param[in]:mu-containing seed(32byte)
* @param[out]c-poly.c
*********************************************/
void poly_SampleInBall(poly* c, uint8_t* mu[SEEDBYTES]);



#endif // !POLY_H

