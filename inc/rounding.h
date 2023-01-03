#ifndef ROUNDING_H
#define ROUNDING_H

#include "../inc/system_para.h"
#include "../inc/deftype.h"

/*********************************************
*Func:Power2Round_q(r,d)
*Compute r0, r1 of r.
* @param[in]:r
* @param[out]:r0-the leaset significant d-bits->1-2^(d-1)
* @param[out]:r1-the most significant part of r(return)
**********************************************/
ssi_t power2round(ssi_t *r0, ssi_t r1, ssi_t r);

/**********************************************
*Func:Decompose_q(r,a)
* Compute r0, r1 of r.
* r=r1*\alpha+a0, a0\in[-\alpha/2,0)
* @param[in]:r
* @param[out]:r0-the leaset significant part of r
* @param[out]:r1-the most significant part of r(return)
**********************************************/
ssi_t decompose(ssi_t* r0, ssi_t r1, ssi_t r);

/*********************************************
*Func:makehint
* Compute the hint bit decided whether the low bits of the r overflow into the high bits
* @param[in]:r
* @param[out]:r0-the leaset significant part of r
* @param[out]:r1-the most significant part of r(return)
* return 1 if overflow
* else return 0
**********************************************/
int makehint(ssi_t r0, ssi_t r1, ssi_t r);

/********************************************
*Func:highbits
* Compute the high bits of r
* @param[in]:r
* @param[out]:r0-the leaset significant part of r
* @param[out]:r1-the most significant part of r(return)
********************************************/
ssi_t highbits(ssi_t r0, ssi_t r1, ssi_t r);

/********************************************
*Func:lowbits
* Compute the high bits of r
* @param[in]:r
* @param[out]:r0-the leaset significant part of r(return)
* @param[out]:r1-the most significant part of r
********************************************/
ssi_t lowbits(ssi_t r0, ssi_t r1, ssi_t r);

/*******************************************************
*Func:usehint
* Return correct high bits according to hint.
* @param[in]:r
* @param[in]:hint=0 or 1
* @param[out]:r0-the leaset significant part of r(return)
* @param[out]:r1-the most significant part of r
********************************************************/
ssi_t usehint(ssi_t r0, ssi_t r1, ssi_t r, int hint);



#endif // ! ROUNDING_H

