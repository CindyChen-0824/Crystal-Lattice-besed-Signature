#include "../inc/rounding.h"
#include "../inc/poly.h"

/*********************************************
*Func:Power2Round_q(r,d)
*Compute r0, r1 of r.
* @param[in]:r
* @param[out]:r0-the leaset significant d-bits->-2^(d-1)+1
* @param[out]:r1-the most significant part of r(return)
**********************************************/
ssi_t power2round(ssi_t *r0, ssi_t r1, ssi_t r)
{
	r1 = (r + (1 << (D - 1)) - 1) >> D;//r1=(r-(1-2^(d-1))/2^d
	*r0 = r - (r1 << D);
	return r1;
}

/**********************************************
*Func:Decompose_q(r,a)
* Compute r0, r1 of r.
* r=r1*\alpha+a0, a0\in[-\alpha/2,0)
* @param[in]:r
* @param[out]:r0-the leaset significant part of r
* @param[out]:r1-the most significant part of r(return)
**********************************************/
ssi_t decompose(ssi_t *r0, ssi_t r1, ssi_t r)//\alpha=88
{
	r1 = (r + (1 << 7) - 1) >> 7;//r0=-2^7+1
	r1 = (r1 * 11275 + (1 << 23)) >> 24;
	r1 ^= ((43 - r1) >> 31) & r1;

	*r0 = r - r1 * 2 * GAMMA2;
	*r0 -= (((Q - 1) / 2 - *r0) >> 31) & Q;
	return r1;
}

/*********************************************
*Func:makehint
* Compute the hint bit decided whether the low bits of the r overflow into the high bits
* @param[in]:r
* @param[out]:r0-the leaset significant part of r
* @param[out]:r1-the most significant part of r(return)
* return 1 if overflow
* else return 0
**********************************************/
int makehint(ssi_t r0, ssi_t r1, ssi_t r)
{
	/*lowbits(r0, r1, r);*/
	if (r1 <= GAMMA2 || r1 > Q - GAMMA2 || (r1 == Q - GAMMA2 && r == 0))
		return 0;
	else
		return 1;//发生溢出
}

/********************************************
*Func:highbits
* Compute the high bits of r
* @param[in]:r
* @param[out]:r0-the leaset significant part of r
* @param[out]:r1-the most significant part of r(return)
********************************************/
ssi_t highbits(ssi_t *r0, ssi_t *r1, ssi_t *r)
{
	decompose(&r0, &r1, &r);
	return r1;
}

/********************************************
*Func:lowbits
* Compute the high bits of r
* @param[in]:r
* @param[out]:r0-the leaset significant part of r(return)
* @param[out]:r1-the most significant part of r
********************************************/
ssi_t lowbits(ssi_t *r0, ssi_t *r1, ssi_t *r)
{
	decompose(&r0, &r1, &r);
	return r0;
}

/*******************************************************
*Func:usehint
* Return correct high bits according to hint.
* @param[in]:r
* @param[in]:hint=0 or 1
* @param[out]:r0-the leaset significant part of r(return)
* @param[out]:r1-the most significant part of r
********************************************************/
ssi_t usehint(ssi_t r0, ssi_t r1, ssi_t r, int hint)//\alpha=88
{
	r1 = decompose(&r0, r1, r);
	/*r0 = lowbits(&r0, &r1, &r);*/
	if (hint == 0)
		return r1;//无进位，直接返回高比特位
	else//hint != 0,有进位
	{
		if (r0 > 0)
			return(r1 == 43) ? 0 : r1 + 1;
		else
			return(r1 == 0) ? 43 : r1 - 1;
	}	
}

