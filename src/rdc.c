#include <stdio.h>
#include "../inc/rdc.h"

/*********************************************************
* Func: mont_rdc
*
* Use Montgomery RDC to compute r' such that -Q< r'<Q
* Element a with -2^(31)< a <2^(31)
* R=2^(32) mod Q
* r'=a*R^-1 mod Q
*
* @param[in]:a-result from ntt
* @param[out]:r-r'
*
**********************************************************/
ssi_t mont_rdc(sdi_t a)
{
	int32_t t;

	t = (int32_t)a * QINV;
	t = (a - (int64_t)t * Q) >> 32;
	return t;
}

/*********************************************************
*Func:rdc_32
*
* Compute r \in [-6283009,6283007] according to a.
* Such that r=a mod Q, where a<=2^31-2^22-1
*
* @param[in]:a
* @param[out]:r
**********************************************************/
ssi_t rdc_32(ssi_t a)
{
	ssi_t t, r;
	t = (a + (1 << 22)) >> 23;//t=(a+2^22)/2^23 <= 255
	r = a - t * Q;

	return r;
}

/*********************************************************
* Func:a_add_q
*
* If a<0, then a+Q;
* else a
*
* @param[in]:a
* @param[out]:r
**********************************************************/
ssi_t a_add_q(ssi_t a)
{
	ssi_t r;
	if (((a >> 31) & 1) != 0)//判断a是否为负数
	{
		a += Q;
	}
	r = a;
	return r;
}