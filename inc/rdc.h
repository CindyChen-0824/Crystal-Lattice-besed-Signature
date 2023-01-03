#ifndef RDC_H
#define RDC_H

#include "../inc/deftype.h"
#include "../inc/system_para.h"

/*********************************************************
* Func: mont_rdc
*
* Transform result in Z_q
* Use Montgomery RDC to compute r' such that -Q< r'<Q
* R=2^(32) mod Q
* r'=a*R^-1 mod Q
*
* @param[in]:a-result from ntt
* @param[out]:r-r'
*
**********************************************************/
ssi_t mont_rdc(sdi_t a);

/*********************************************************
*Func:rdc_32
* 
* Compute r \in [-6283009,6283007] according to a.
* Such that r=a mod Q, where a<=2^31-2^22-1
* 
* @param[in]:a
* @param[out]:r
**********************************************************/
ssi_t rdc_32(ssi_t a);

/*********************************************************
* Func:a_add_q
* 
* If a<0, then a+Q;
* else a
* 
* @param[in]:a
* @param[out]:r
**********************************************************/
ssi_t a_add_q(ssi_t a);

#endif // !RDC_H

