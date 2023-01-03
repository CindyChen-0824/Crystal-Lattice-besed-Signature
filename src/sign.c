#include "../inc/randbyte.h"
#include "../inc/polyvct.h"
#include "../inc/packing.h"
#include "../inc/sign.h"

/***************************************
*Func:KeyGen
*
* Generate public key and secrete key.
* Returns 0 if success.
*
* @param[out]:pk
* @param[out]:sk
***************************************/
int KeyGen(uint8_t* pk, uint8_t* sk)
{
	uint8_t seedbuf[3 * SEEDBYTES] = { 0 };//zeta=256*3=96*8
	uint8_t tr[CRHBYTES] = { 0 };//48*8=384
	uint8_t* rho, * sigma, * key;
	polyvctl mat[K];
	polyvctl s1, s1p;
	polyvctk s2, t0, t1;

	/*01-02:随机化种子空间,rho,sigma,key*/
 	rand_byte(seedbuf, SEEDBYTES);//get seed
	shake256(seedbuf, 3 * SEEDBYTES, seedbuf, SEEDBYTES);//01
	rho = seedbuf;
	sigma = rho + SEEDBYTES;
	key = seedbuf + 2 * SEEDBYTES;//02:tr=rho||sigma||key
	                                                                                                        
	/*03:s1,s2拒绝采样*/
	polyvctl_uniform_eta(&s1, sigma, 0);//s1
	polyvctk_uniform_eta(&s2, sigma, L);//s2//03
	
	/*04:Matrix Expand*/
	poly_ExpandA(mat, rho);//04, A is in NTT.

	/*05:t=As1+s2*/
	s1p = s1;
	polyvctl_ntt(&s1p);//NTT(s1')
	polyvct_matrix_mont_mul(&t1, mat, &s1p);//t1=t1'*A in Mont
	polyvctk_rdc(&t1);//t1 Mont->normal
	polyvctk_invntt_tomont(&t1);//NTT(^-1)(s1) in Mont
	polyvctk_add(&t1, &t1, &s2);//t1=As1+s2
	/*s1 = s1p;*/

	/*06:Power2Round t1*/
	polyvctk_add_q(&t1);
	polyvctk_power2round(&t0, &t1, &t1);//06

	/*07-08:Packing sk*/
	pk_packing(pk, rho, &t1);//pk=(rho||t1)
	shake256(tr, CRHBYTES, pk, PK_SIZE);//07,tr=CRH(rho||t1)
	sk_packing(sk, rho, key, tr, &s1, &s2, &t0);//08

	return 0;
}

/*******************************************
*Func:Sign
*
* Signing
* Returns 0 if success, else returns 1.
*
* @param[in]:sk-secrete key
* @param[in]:M-message
* @param[in]:Mlen-the length of message
* @param[out]:sig-the signature
* @param[out]:siglen-the length of signature
********************************************/
int Sign(uint8_t* sk, const uint8_t* M, size_t Mlen, uint8_t* sig, size_t siglen)
{
	unsigned int hint;
	uint8_t seedbuf[2 * SEEDBYTES + 3 * CRHBYTES];
	uint8_t* rho, * rhop, * key, * tr, * mu;
	ssi_t nonce = 0;
	polyvctl mat[K];
	polyvctl s1, y, z;
	polyvctk s2, t0, t1, w, w0, w1, h, r, r0, r1;
	poly cp;
	keccak_state state;

	/*Pre-compute*/
	rho = seedbuf;
	tr = rho + SEEDBYTES;
	key = tr + CRHBYTES;
	mu = key + SEEDBYTES;
	rhop = mu + CRHBYTES;
	sk_unpacking(rho, key, tr, &s1, &s2, &t0, sk);
	/*sig = rhop + SEEDBYTES + CRHBYTES;*/

	/*10:CRH(tr,M)*/
	shake256_init(&state);
	shake256_absorb(&state, tr, CRHBYTES);
	shake256_absorb(&state, M, Mlen);
	shake256_finalize(&state);
	shake256_squeeze(mu, CRHBYTES, &state);

	/*12:CRH(key,mu)*/
	shake256(rhop, CRHBYTES, key, SEEDBYTES + CRHBYTES);
	/*sig = rhop + SEEDBYTES + CRHBYTES;*/

	/*09:Matrix Expand*/
	poly_ExpandA(mat, rho);
	polyvctl_ntt(&s1);
	polyvctk_ntt(&s2);
	polyvctk_ntt(&t0);

	/*14-21:while(z,h)=rej*/
rej:
	/*14:Sampling y*/
	polyvctl_uniform_gamma1(&y, rhop, nonce++);

	/*15:w=Ay*/
	z = y;
	polyvctk_ntt(&z);
	polyvct_matrix_mont_mul(&w, mat, &z);
	polyvctk_rdc(&w);
	polyvctk_invntt_tomont(&w);

	/*16:w->w1*/
	polyvctk_add_q(&w);
	polyvctk_highbits(&w0, &w1, &w);
	polyvctk_pack_w1(sig, &w1);

	/*17-18:cp=H(mu,w1),Sampleball(cp)*/
	shake256_init(&state);
	shake256_absorb(&state, mu, CRHBYTES);
	shake256_absorb(&state, sig, K * W1_PACKSIZE);
	shake256_finalize(&state);
	shake256_squeeze(sig, SEEDBYTES, &state);
	poly_SampleInBall(&cp, sig);
	poly_ntt(&cp);

	/*19:z=y+cp*s1*/
	polyvctl_mul_inmont(&z, &cp, &s1);
	polyvctl_invntt_tomont(&z);//z=NTT^(-1)(cp*s1)
	polyvctl_add(&z, &y, &z);//z=y+(cp*s1)
	polyvctl_rdc(&z);
	if (polyvctl_checknorm(&z, GAMMA1 - BETA))
		goto rej;//21:Check if z1>=gamma1-beta

	/*20:Lowbits(w-cs2)*/
 	polyvctk_mul_inmont(&h, &cp, &s2);
	polyvctk_invntt_tomont(&h);//h=NTT^(-1)(cp*s2)
	polyvctk_sub(&r0, &w0, &h);//r0=w-h
	polyvctk_rdc(&r0);
	r = r0;//r=w-c*s2
	//polyvctk_lowbits(&r0, &r1, &r);
	if (polyvctk_checknorm(&r, GAMMA2 - BETA))
		goto rej;//21:Check if r0>=gamma2-beta

	/*23-24:ct0,hint*/
	polyvctk_mul_inmont(&h, &cp, &t0);
	polyvctk_invntt_tomont(&h);//h=NTT^(-1)(cp*t0)
	polyvctk_rdc(&h);//Mont to Normal
	if (polyvctk_checknorm(&h, GAMMA2))
		goto rej;//24:Check if ct0>=gamma2
	polyvctk_add(&r, &r, &h);//w-cs2+ct0
	polyvctk_add_q(&r);
	hint = polyvctk_makehint(&h, &r, &w1);
	if (hint > OMEGA)
		goto rej;//24:Check if hint>omega
	
	/*26:Packing the signature*/
	sig_packing(sig, &z, &h, sig);
	return 0;
}

/*******************************************
*Func:Verify
*
* Verify
* Returns 0 if success, else returns 1.
*
* @param[in]:pk-public key
* @param[in]:M-message
* @param[in]:Mlen-the length of message
* @param[in]:sig-the signature
* @param[in]:siglen-the length of signature
********************************************/
int Verify(const uint8_t* pk, const uint8_t* M, size_t Mlen, const uint8_t* sig, size_t siglen)
{
	uint8_t buf[K * W1_PACKSIZE];
	uint8_t rho[SEEDBYTES], mu[CRHBYTES], c[SEEDBYTES], c2[SEEDBYTES];
	poly cp;
	polyvctl mat[K];
	polyvctl z;
	polyvctk t1, w0, w1, h;
	keccak_state state;
	int i, j, hint = 0;

	if (siglen != SIG_SIZE)
		return 1;//首先判断签名长度

	/*Pre*/
	pk_unpacking(rho, &t1, pk);
	if (sig_unpacking(&z, &h, c, sig) == 1)
		return 1;
	if (polyvctl_checknorm(&z, GAMMA1 - BETA))
		return 1;//31:Check if z<=gamma1-beta

	/*27:Matrix Expand*/
	poly_ExpandA(mat, rho);

	/*28:CRH(CRH(rho||t1)||M)*/
	shake256(mu, CRHBYTES, pk, PK_SIZE);
	shake256_init(&state);
	shake256_absorb(&state, mu, CRHBYTES);
	shake256_absorb(&state, M, Mlen);
	shake256_finalize(&state);
	shake256_squeeze(mu, CRHBYTES, &state);

	/*29:SampleInBall(cp)*/
	poly_SampleInBall(&cp, c);

	/*30:Compute w1'*/
	polyvctl_ntt(&z);//NTT(z)
	polyvct_matrix_mont_mul(&w1, mat, &z);//w1=Az
	poly_ntt(&cp);//NTT(cp)
	polyvctk_lsh(&t1, &t1);//t1*2^d
	polyvctk_ntt(&t1);//NTT(t1*2^d)

	polyvctk_mul_inmont(&t1, &cp, &t1);//t1=t1*cp
	polyvctk_sub(&w1, &w1, &t1);//w1=Az-t1*cp
	polyvctk_rdc(&w1);
	polyvctk_invntt_tomont(&w1);//NTT^(-1)(w1)

	polyvctk_add_q(&w1);
	polyvctk_usehint(&w1, &w0, &w1, &w1, &h);
	polyvctk_pack_w1(buf, &w1);

	/*31:Check c'=H(mu||w1') and if h>=omega*/
	shake256_init(&state);
	shake256_absorb(&state, mu, CRHBYTES);
	shake256_absorb(&state, buf, K * W1_PACKSIZE);
	shake256_finalize(&state);
	shake256_squeeze(c2, SEEDBYTES, &state);
	for (i = 0; i < SEEDBYTES; ++i)
	{
		if (c[i] != c2[i])
			return 1;
	}

	for (i = 0; i < K; ++i)
	{
		for (j = 0; j < N; ++j)
		{
			if (h.vctk[i].coff[j] == 1)
				hint++;
		}
		if (hint > OMEGA)
			return 1;
	}
	return 0;
}


