#include "../inc/poly.h"
#include "../inc/ntt.h"
#include "../inc/rounding.h"
#include "../inc/rej_uniform.h"
#include "../inc/fips202.h"
#include "../inc/polyvct.h"
#include "../inc/packing.h"

/*Basic Operation*/
/*********************************************
*Func:poly_rdc
*
* Reduce all coefficients of poly. a in range [-6283009,6283007]
*
* @param[in]:a-poly
*********************************************/
void poly_rdc(poly* a)
{
	int i;
	for (i = 0; i < N; ++i)
	{
		a->coff[i] = rdc_32(a->coff[i]);
	}
}

/***********************************************
* Func:poly_coff_add_q
*
* For any negative coeddicients of poly.a
* Add Q to thme.
*
* @param[in]:a-poly
************************************************/
void poly_coff_add_q(poly* a)
{
	int i;
	for (i = 0; i < N; ++i)
	{
		a->coff[i] = a_add_q(a->coff[i]);
	}
}

/***********************************************
*Func:poly_add
*
* Poly Addition:r=a+b
*
* @param[in]:a-poly a
* @param[in]:b-poly b
* @param[out]:r-poly r, result
************************************************/
void poly_add(poly* r, poly* a, poly* b)
{
	int i;
	for (i = 0; i < N; ++i)
	{
		r->coff[i] = a->coff[i] + b->coff[i];
	}
}

/***********************************************
*Func:poly_sub
*
* Poly Substraction:r=a-b
*
* @param[in]:a-poly a
* @param[in]:b-poly b
* @param[out]:r-poly r, result
************************************************/
void poly_sub(poly* r, poly* a, poly* b)
{
	int i;
	for (i = 0; i < N; ++i)
	{
		r->coff[i] = a->coff[i] - b->coff[i];
	}
}

/***********************************************
*Func:poly_lsh
*
* Multiply poly.a by 2^13 without reduction.
* Assume all coefficients <=2^18
*
* @param[in]:a-poly a
* @param[out]:r-poly r
************************************************/
void poly_lsh(poly* r, poly* a)
{
	int i;
	for (i = 0; i < N; ++i)
	{
		r->coff[i] = a->coff[i] << D;
	}
}

/*Poly. NTT/INTT*/
/***********************************************
*Func:poly_ntt
*
* Forward ntt for coefficients of poly.a
*
*@param[in]:a-poly a
************************************************/
void poly_ntt(poly* a)
{
	ntt(a->coff);
}

/***********************************************
*Func:poly_invntt_tomont
*
* Inverse ntt for coefficients of poly.a in Montgomary domain.
*
*@param[in]:a-poly a
************************************************/
void poly_invntt_tomont(poly* a)
{
	invntt_tomont(a->coff);
}

/***********************************************
*Func:poly_mul_inmont
*
* Multiply two poly.s a and b in Montgomary domain.
*
* @param[in]:a-poly a
* @param[in]:b-poly b
* @param[out]:r-poly r, result
************************************************/
void poly_mul_inmont(poly* r, poly* a, poly* b)
{
	int i;
	for (i = 0; i < N; ++i)
	{
		r->coff[i] = mont_rdc((sdi_t)a->coff[i] * b->coff[i]);
	}
}

/*Poly. Rounding*/
/************************************************
*Func:poly_power2round
*
* Power2round for poly.a's coefficients
*
* @param[in]:a-poly a
* @param[out]:a0-poly a0->low bits of coefficients of a
* @param[out]:a1-poly a1->high bits of coefficients of a
************************************************/
void poly_power2round(poly* a0, poly* a1, poly* a)
{
	int i;
	for (i = 0; i < N; ++i)
	{
		a1->coff[i] = power2round(&a0->coff[i], a1->coff[i], a->coff[i]);
	}
}

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
void poly_decompose(poly* a0, poly* a1, poly* a)
{
	int i;
	for (i = 0; i < N; ++i)
	{
		a1->coff[i] = decompose(&a0->coff[i], a1->coff[i], a->coff[i]);
	}
}

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
int poly_makehint(poly* a0, poly* a1, poly* a)
{
	int i, sumh = 0;
	for (i = 0; i < N; ++i)
	{
		a0->coff[i] = makehint(a0->coff[i], a1->coff[i], a->coff[i]);
		sumh += a0->coff[i];
	}
	return sumh;
}

/**********************************************************
*Func:poly_highbits
*
* Returns highbits for poly.a's coefficients
*
* @param[in]:a-poly a
* @param[out]:a0-poly a0->low bits of coefficients of a
* @param[out]:a1-poly a1->high bits of coefficients of a
***********************************************************/
void poly_highbits(poly* a0, poly* a1, poly* a)
{
	int i;
	for (i = 0; i < N; ++i)
	{
		a1->coff[i] = decompose(&a0->coff[i], a1->coff[i], a->coff[i]);
	}
}

/**********************************************************
*Func:poly_lowbits
*
* Returns lowbits for poly.a's coefficients
*
* @param[in]:a-poly a
* @param[out]:a0-poly a0->low bits of coefficients of a
* @param[out]:a1-poly a1->high bits of coefficients of a
***********************************************************/
void poly_lowbits(poly* a0, poly* a1, poly* a)
{
	int i;
	for (i = 0; i < N; ++i)
	{
		a0->coff[i] = lowbits(a0->coff[i], a1->coff[i], a->coff[i]);
	}
}

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
void poly_usehint(poly* r, poly* a0, poly* a1, poly* a, poly* h)
{
	int i;
	for (i = 0; i < N; ++i)
	{
		r->coff[i] = usehint(a0->coff[i], a1->coff[i], a->coff[i], h->coff[i]);
	}
}

/*Poly. Uniform*/
/*********************************************
*Func:poly_checknorm
*
* Check norm if all are in [-B,B].B<=(Q-1)/8
* Returns 1 if it is not, else returns 0.
*
* @param[in]:a-poly a
* @param[in]:B-norm limitation
*********************************************/
int poly_checknorm(poly* a, ssi_t B)
{
	int i;
	ssi_t t, k;

	if (B > NORMLIM)
		return 1;

	/*求数的绝对值*/
	for (i = 0; i < N; ++i)
	{
		t = a->coff[i] >> 31;//取符号位
		t = a->coff[i] - (t & 2 * a->coff[i]);//正数不变，负数取反+1

		if (t >= B)
			return 1;
	}

		return 0;
}

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
void poly_uni(poly* a, uint8_t* seed, ssi_t nonce)
{
	int i, ctr, off;
	int buflen = UNI_NBLOCKS * STREAM128_BLOCKBYTES;//len(buf):840
	uint8_t buf[UNI_NBLOCKS * STREAM128_BLOCKBYTES + 2];//Output:842->seed||nonce
	keccak_state state;

	SHAKE128_INIT(&state, seed, nonce);//Input:seed||nonce->F
	SHAKE128_SQBLOCKS(buf, UNI_NBLOCKS, &state);//Output:->F

	ctr = rej_uni(a->coff, N, buf, buflen);//拒绝抽样一次返回的poly.a系数数量

	while (ctr < N)
	{
		off = buflen & 0x02;//buflen%3
		for (i = 0; i < off; ++i)
			buf[i] = buf[buflen - off + i];

		SHAKE128_SQBLOCKS(buf + off, 1, &state);
		buflen = STREAM128_BLOCKBYTES + off;
		ctr += rej_uni(a->coff + ctr, N - ctr, buf, buflen);
	}
}

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
void poly_uni_eta(poly* a, uint8_t* seed, ssi_t nonce)
{
	int ctr;
	int buflen = UNI_ETA_NBLOCKS * STREAM128_BLOCKBYTES;//2*168
	uint8_t buf[UNI_ETA_NBLOCKS * STREAM128_BLOCKBYTES];//138
	keccak_state state;

	SHAKE128_INIT(&state, seed, nonce);
	SHAKE128_SQBLOCKS(buf, UNI_ETA_NBLOCKS, &state);

	ctr = rej_eta(a->coff, N, buf, buflen);

	while (ctr < N)
	{
		SHAKE128_SQBLOCKS(buf, 1, &state);
		ctr += rej_eta(a->coff + ctr, N - ctr, buf, STREAM128_BLOCKBYTES);
	}
}


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
void poly_uni_gamma1(poly* a, uint8_t* seed, ssi_t nonce)
{
	uint8_t buf[UNI_GAMMA1_NBLOCKS * SHAKE256_RATE];
	keccak_state state;

	SHAKE256_INIT(&state, seed, nonce);
	SHAKE256_SQBLOCKS(buf, UNI_GAMMA1_NBLOCKS, &state);
	bit_unpacking_z(a, buf);
}
/*********************************************
*Func:poly_ExpandA
*
* Implementation of ExpandA.
*
* @param[out]:mat-output matrix
* @param[in]:rho-seed rho(256bit)
********************************************/
void poly_ExpandA(polyvctl mat[K], uint8_t* rho)
{
	int i, j;
	for (i = 0; i < K; ++i)
	{
		for (j = 0; j < L; ++j)
		{
			poly_uni(&mat[i].vctl[j], rho, (i << 8) + j);
		}
	}
}

/*********************************************
*Func:poly_SampleInBall
*
* Implementation of SampleInBall
*
* @param[in]:mu-containing seed(32byte)
* @param[out]c-poly.c
*********************************************/
void poly_SampleInBall(poly* c, uint8_t mu[SEEDBYTES])
{
	int i, b, pos;
	sdi_t signs = 0;
	uint8_t buf[SHAKE256_RATE];
	keccak_state state;

	shake256_init(&state);
	shake256_absorb(&state, mu, SEEDBYTES);
	shake256_finalize(&state);
	shake256_squeezeblocks(buf, 1, &state);

	for (i = 0; i < 8; ++i)
	{
		signs |= (sdi_t)buf[i] << 8 * i;
	}
	pos = 8;

	/*SampleInBall*/
	for (i = 0; i < N; ++i)
	{
		c->coff[i] = 0;
	}
	for (i = N - TAU; i < N; ++i)
	{
		do
		{
			if (pos >= SHAKE256_RATE)
			{
				shake256_squeezeblocks(buf, 1, &state);
				pos = 0;
			}
			b = buf[pos++];
		} while (b > i);
	
		c->coff[i] = c->coff[b];
		c->coff[b] = 1 - 2 * (signs & 1);//(-1)^s(奇数次为-1,偶数次为1）
		signs >>= 1;
	}
}



