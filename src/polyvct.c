#include "../inc/polyvct.h"
#include "../inc/ntt.h"
#include "../inc/rej_uniform.h"
#include "../inc/packing.h"

/*Vectors of poly.s of length L*/
/************************************************
* Func:polyvctl_rdc
*
* Reduce all coefficients of polyvctl. a in range [-6283009,6283007]
*
* @param[in]:v-polyvctl
************************************************/
void polyvctl_rdc(polyvctl* v)
{
	int i;
	for (i = 0; i < L; ++i)
	{
		poly_rdc(&v->vctl[i]);
	}
}

/***********************************************
*Func:polyvctl_add
*
* Polyvct Addition:r=a+b
*
* @param[in]:va-polyvct a
* @param[in]:vb-polyvct b
* @param[out]:r-polyvct r, result
************************************************/
void polyvctl_add(polyvctl* r, polyvctl* va, polyvctl* vb)
{
	int i;
	for (i = 0; i < L; ++i)
	{
		poly_add(&r->vctl[i], &va->vctl[i], &vb->vctl[i]);
	}
}

/***********************************************
*Func:polyvctl_ntt
*
* Forward ntt for coefficients of polyvct.v
*
*@param[in]:v-polyvct v
************************************************/
void polyvctl_ntt(polyvctl* v)
{
	int i;
	for (i = 0; i < L; ++i)
	{
		poly_ntt(&v->vctl[i]);
	}
}

/***********************************************
*Func:polyvctl_invntt_tomont
*
* Inverse ntt for coefficients of polyvct.v in Montgomary domain.
*
*@param[in]:v-polyvct v
************************************************/
void polyvctl_invntt_tomont(polyvctl* v)
{
	int i;
	for (i = 0; i < L; ++i)
	{
		poly_invntt_tomont(&v->vctl[i]);
	}
}

/***********************************************
*Func:polyvctl_mul_inmont
*
* Multiply two polyvct.s va and vb in Montgomary domain.
*
* @param[in]:va-polyvct a
* @param[in]:vb-polyvct b
* @param[out]:r-polyvct r, result
************************************************/
void polyvctl_mul_inmont(polyvctl* r, poly* va, polyvctl* vb)
{
	int i;
	for (i = 0; i < L; ++i)
	{
		poly_mul_inmont(&r->vctl[i], va, &vb->vctl[i]);
	}
}

/************************************************
*Func:polyvctl_mul_acc_inmont
*
*Multiply two polyvct.s va and vb in Montgomary domain.
*
* @param[in]:va-polyvct a
* @param[in]:vb-polyvct b
* @param[out]:w-polyvct w, result
************************************************/
void polyvctl_mul_acc_inmont(poly* w, polyvctl* va, polyvctl* vb)
{
	int i;
	poly t;

	poly_mul_inmont(w, &va->vctl[0], &vb->vctl[0]);
	for (i = 1; i < L; ++i)
	{
		poly_mul_inmont(&t, &va->vctl[i], &vb->vctl[i]);
		poly_add(w, w, &t);
	}
}

/*********************************************
*Func:polyvctl_checknorm
*
* Check norm of polyvctl if all are in [-B,B].B<=(Q-1)/8
* Returns 1 if it is not, else returns 0.
*
* @param[in]:a-poly a
* @param[in]:B-norm limitation
*********************************************/
int polyvctl_checknorm(polyvctl* v, ssi_t B)
{
	int i;
	for (i = 0; i < L; ++i)
	{
		if (poly_checknorm(&v->vctl[i], B) == 1)
			return 1;
	}

	return 0;
}
/*********************************************************
*Func:polyvctl_uniform_eta
*
* Sampling poly. with uniformly random coefficients
* in [-GAMMA1+1,GAMMA1] by rejection sampling.
*
* @param[in]:a-poly a
* @param[in]:seed-byte array with seed of length SEEDBYTES
* @param[in]:nonce-2 bytes
********************************************************/
void polyvctl_uniform_eta(polyvctl* v, uint8_t seed[SEEDBYTES], ssi_t nonce)
{
	int i;
	for (i = 0; i < L; ++i)
	{
		poly_uni_eta(&v->vctl[i], seed, nonce++);
	}
}

/*********************************************************
*Func:polyvctl_uniform_gamma1
*
* Sampling poly. with uniformly random coefficients
* in [-GAMMA1+1,GAMMA1] by rejection sampling.
*
* @param[in]:a-poly a
* @param[in]:seed-byte array with seed of length SEEDBYTES
* @param[in]:nonce-2 bytes
********************************************************/
void polyvctl_uniform_gamma1(polyvctl* v, uint8_t seed[SEEDBYTES], ssi_t nonce)
{
	int i;
	for (i = 0; i < L; ++i)
	{
		poly_uni_gamma1(&v->vctl[i], seed, L * nonce + i);
	}
}

/************************************************************************************************************/

/*Vectors of poly.s of length K*/
/************************************************
* Func:polyvctk_rdc
*
* Reduce all coefficients of polyvctl. a in range [-6283009,6283007]
*
* @param[in]:v-polyvctl
************************************************/
void polyvctk_rdc(polyvctk* v)
{
	int i;
	for (i = 0; i < K; ++i)
	{
		poly_rdc(&v->vctk[i]);
	}
}

/************************************************
*Func:polyvctk_add_q
*
* For all coefficients of poly. in vector of length K
* add Q if it is negative.
*
* @param[in]:v-polyvctk
************************************************/
void polyvctk_add_q(polyvctk* v)
{
	int i;
	for (i = 0; i < K; ++i)
	{
		poly_coff_add_q(&v->vctk[i]);
	}
}
/***********************************************
*Func:polyvctk_add
*
* Polyvct Addition:r=a+b
*
* @param[in]:va-polyvct a
* @param[in]:vb-polyvct b
* @param[out]:r-polyvct r, result
************************************************/
void polyvctk_add(polyvctk* r, polyvctk* va, polyvctk* vb)
{
	int i;
	for (i = 0; i < K; ++i)
	{
		poly_add(&r->vctk[i], &va->vctk[i], &vb->vctk[i]);
	}
}

/***********************************************
*Func:polyvctk_sub
*
* Polyvct Substraction:r=a-b
*
* @param[in]:va-polyvct a
* @param[in]:vb-polyvct b
* @param[out]:r-polyvct r, result
************************************************/
void polyvctk_sub(polyvctk* r, polyvctk* va, polyvctk* vb)
{
	int i;
	for (i = 0; i < K; ++i)
	{
		poly_sub(&r->vctk[i], &va->vctk[i], &vb->vctk[i]);
	}
}

/***********************************************
*Func:polyvctk_lsh
*
* Multiply poly.a by 2^13 without reduction.
* Assume all coefficients <=2^18
*
* @param[in]:a-polyvct a
* @param[out]:r-polyvct r, result
************************************************/
void polyvctk_lsh(polyvctk* r, polyvctk* v)
{
	int i;
	for (i = 0; i < K; ++i)
	{
		poly_lsh(&r->vctk[i], &r->vctk[i]);
	}
}

/***********************************************
*Func:polyvctk_ntt
*
* Forward ntt for coefficients of polyvct.v
*
*@param[in]:v-polyvct v
************************************************/
void polyvctk_ntt(polyvctk* v)
{
	int i;
	for (i = 0; i < K; ++i)
	{
		poly_ntt(&v->vctk[i]);
	}
}

/***********************************************
*Func:polyvctk_invntt_tomont
*
* Inverse ntt for coefficients of polyvct.v in Montgomary domain.
*
*@param[in]:v-polyvct v
************************************************/
void polyvctk_invntt_tomont(polyvctk* v)
{
	int i;
	for (i = 0; i < K; ++i)
	{
		poly_invntt_tomont(&v->vctk[i]);
	}
}

/***********************************************
*Func:polyvctk_mul_inmont
*
* Multiply two polyvct.s va and vb in Montgomary domain.
*
* @param[in]:va-polyvct a
* @param[in]:vb-polyvct b
* @param[out]:r-polyvct r, result
************************************************/
void polyvctk_mul_inmont(polyvctk* r, poly* va, polyvctk* vb)
{
	int i;
	for (i = 0; i < K; ++i)
	{
		poly_mul_inmont(&r->vctk[i], va, &vb->vctk[i]);
	}
}

/************************************************
*Func:polyvctk_mul_acc_inmont
*
*Multiply two polyvct.s va and vb in Montgomary domain.
*
* @param[in]:va-polyvct a
* @param[in]:vb-polyvct b
* @param[out]:w-polyvct w, result
************************************************/
void polyvctk_mul_acc_inmont(polyvctk* w, polyvctk* va, polyvctk* vb)
{
	int i;
	poly t;
	poly_mul_inmont(&w->vctk[0], &va->vctk[0], &vb->vctk[0]);
	for (i = 1; i < K; ++i)
	{
		poly_mul_inmont(&t, &va->vctk[i], &vb->vctk[i]);
	}
	polyvctk_add(w, w, &t);
}

/*****************************************************************
*Func:polyvctk_power2round
*
* Power2round for vectors of polyvctk.v's coefficients
*
* @param[in]:v-polyvctk v
* @param[out]:v0-polyvctk v0->low bits of coefficients of v
* @param[out]:v1-polyvctk v1->high bits of coefficients of v
******************************************************************/
void polyvctk_power2round(polyvctk* v0, polyvctk* v1, polyvctk* v)
{
	int i;
	for (i = 0; i < K; ++i)
	{
		poly_power2round(&v0->vctk[i], &v1->vctk[i], &v->vctk[i]);
	}
}

/**************************************************************
*Func:polyvctk_decompose
*
* Decompose for vectors of polyvctk.v's coefficients
*
* @param[in]:v-polyvctk v
* @param[out]:v0-polyvctk v0->low bits of coefficients of v
* @param[out]:v1-polyvctk v1->high bits of coefficients of v
**************************************************************/
void polyvctk_decompose(polyvctk* v0, polyvctk* v1, polyvctk* v)
{
	int i;
	for (i = 0; i < K; ++i)
	{
		poly_decompose(&v0->vctk[i], &v1->vctk[i], &v->vctk[i]);
	}
}

/*****************************************************************************
*Func:polyvctk_usehint
*
* Compute hint for vectors of polyvctk.v's coefficients
* Rreturns the summary of hints for each coefficients of vectors of polyvctk.v.
*
* @param[in]:v-polyvctk v
* @param[out]:v0-polyvctk v0->low bits of coefficients of v
* @param[out]:v1-polyvctk v1->high bits of coefficients of v
* @param[in]:h-hint polyvctk.
* @param[out]:r-polyvctk r
******************************************************************************/
int polyvctk_usehint(polyvctk* r, polyvctk* v0, polyvctk* v1, polyvctk* v, polyvctk* h)
{
	int i;
	for (i = 0; i < K; ++i)
	{
		poly_usehint(&r->vctk[i], &v0->vctk[i], &v1->vctk[i], &v->vctk[i], &h->vctk[i]);
	}
}

/***************************************************************************
*Func:polyvctk_highbits
*
* Returns highbits for vectors of polyvctk.v's coefficients
*
* @param[in]:v-polyvctk v
* @param[out]:v0-polyvctk v0->low bits of coefficients of v
* @param[out]:v1-polyvctk v1->high bits of coefficients of v
***************************************************************************/
void polyvctk_highbits(polyvctk* v0, polyvctk* v1, polyvctk* v)
{
	int i;
	for (i = 0; i < K; ++i)
	{
		poly_decompose(&v0->vctk[i], &v1->vctk[i], &v->vctk[i]);
	}
}

/***************************************************************************
*Func:polyvctk_lowbits
*
* Returns lowbits for vectors of polyvctk.v's coefficients
*
* @param[in]:v-polyvctk v
* @param[out]:v0-polyvctk v0->low bits of coefficients of v
* @param[out]:v1-polyvctk v1->high bits of coefficients of v
***************************************************************************/
void polyvctk_lowbits(polyvctk* v0, polyvctk* v1, polyvctk* v)
{
	int i;
	for (i = 0; i < K; ++i)
	{
		poly_lowbits(&v0->vctk[i], &v1->vctk[i], &v->vctk[i]);
	}
}

/****************************************************
*Func:polyvctk_makehint
*
* Usehint for vectors of polyvctk.v's coefficients
* Return correct high bits according to hint.
*
* @param[in]:v-polyvctk v
* @param[out]:v0-polyvctk v0->low bits of coefficients of v
* @param[out]:v1-polyvctk v1->high bits of coefficients of v
*****************************************************/
int polyvctk_makehint(polyvctk* v0, polyvctk* v1, polyvctk* v)
{
	int i, H = 0;
	for (i = 0; i < K; ++i)
	{
		H += poly_makehint(&v0->vctk[i], &v1->vctk[i], &v->vctk[i]);
	}
	return H;
}
/*********************************************
*Func:polyvctk_checknorm
*
* Check norm of polyvctk if all are in [-B,B].B<=(Q-1)/8
* Returns 1 if it is not, else returns 0.
*
* @param[in]:a-poly a
* @param[in]:B-norm limitation
*********************************************/
int polyvctk_checknorm(polyvctk* v, ssi_t B)
{
	int i;
	for (i = 0; i < K; ++i)
	{
		if (poly_checknorm(&v->vctk[i], B) == 1)
			return 1;
	}

	return 0;
}
/*********************************************************
*Func:polyvctk_uniform_eta
*
* Sampling poly. with uniformly random coefficients
* in [-GAMMA1+1,GAMMA1] by rejection sampling.
*
* @param[in]:a-poly a
* @param[in]:seed-byte array with seed of length SEEDBYTES
* @param[in]:nonce-2 bytes
********************************************************/
void polyvctk_uniform_eta(polyvctk* v, uint8_t seed[CRHBYTES], ssi_t nonce)
{
	int i;
	for (i = 0; i < K; ++i)
	{
		poly_uni_eta(&v->vctk[i], seed, nonce++);
	}
}

/*********************************************************
*Func:polyvctk_uniform_gamma1
*
* Sampling poly. with uniformly random coefficients
* in [-GAMMA1+1,GAMMA1] by rejection sampling.
*
* @param[in]:a-poly a
* @param[in]:seed-byte array with seed of length SEEDBYTES
* @param[in]:nonce-2 bytes
********************************************************/
void polyvctk_uniform_gamma1(polyvctk* v, uint8_t seed[CRHBYTES], ssi_t nonce)
{
	int i;
	for (i = 0; i < K; ++i)
	{
		poly_uni_gamma1(&v->vctk[i], seed, K * nonce + i);
	}
}

/************************************************
*Func:polyvctk_pack_w1
*
* Implementation for Bit-packing w1
*
* @param[in]:a-Poly.a to be packed
* @param[out]:r-Poly.r the result
************************************************/
void polyvctk_pack_w1(uint8_t r[K * W1_PACKSIZE], polyvctk* w1)
{
	int i;
	for (i = 0; i < K; ++i)
	{
		bit_packing_w1(&r[i * W1_PACKSIZE], &w1->vctk[i]);
	}
}

/***********************************************
*Func:polyvct_matrix_mont_mul
*
* Matrix multiplication in Mont.
*
* @param[out]:r-polyvctk r
* @param[in]:mat-polyvct mat(in k)
* @param[in]:v-polyvctl v
***********************************************/
void polyvct_matrix_mont_mul(polyvctk* r, const polyvctl mat[K], polyvctl* v)
{
	int i;
	for (i = 0; i < K; ++i)
	{
		polyvctl_mul_acc_inmont(&r->vctk[i], &mat[i], v);
	}
}