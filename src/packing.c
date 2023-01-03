#include "../inc/packing.h"

/************************************
*Func:bit_packing_w1
*
* Implementation for Bit-packing w1
*
* @param[in]:a-Poly.a to be packed
* @param[out]:r-Poly.r the result
************************************/
void bit_packing_w1(uint8_t* r, poly* a)
{
	int i;
	for (i = 0; i < W1_PACKSIZE/3; ++i)
	{
		r[3 * i + 0] = a->coff[4 * i + 0];
		r[3 * i + 0] |= a->coff[4 * i + 1] << 6;
		r[3 * i + 1] = a->coff[4 * i + 1] >> 2;
		r[3 * i + 1] |= a->coff[4 * i + 2] << 4;
		r[3 * i + 2] = a->coff[4 * i + 2] >> 4;
		r[3 * i + 2] |= a->coff[4 * i + 3] << 2;
	}
}

/************************************
*Func:bit_packing_z
*
* Implementation for Bit-packing w1
*
* @param[in]:a-Poly.a to be packed
* @param[out]:r-the result
************************************/
void bit_packing_z(uint8_t* r, poly* a)
{
	ssi_t temp[4];
	int i;
	for (i = 0; i < Z_PACKSIZE / 9; ++i)
	{
		temp[0] = GAMMA1 - a->coff[4 * i + 0];
		temp[1] = GAMMA1 - a->coff[4 * i + 1];
		temp[2] = GAMMA1 - a->coff[4 * i + 2];
		temp[3] = GAMMA1 - a->coff[4 * i + 3];

		r[9 * i + 0] = temp[0];
		r[9 * i + 1] = temp[0] >> 8;
		r[9 * i + 2] = temp[0] >> 16;
		r[9 * i + 2] |= temp[1] << 2;
		r[9 * i + 3] = temp[1] >> 6;
		r[9 * i + 4] = temp[1] >> 14;
		r[9 * i + 4] |= temp[2] << 4;
		r[9 * i + 5] = temp[2] >> 4;
		r[9 * i + 6] = temp[2] >> 12;
		r[9 * i + 6] |= temp[3] << 6;
		r[9 * i + 7] = temp[3] >> 2;
		r[9 * i + 8] = temp[3] >> 10;
	}
}

/************************************
*Func:bit_packing_z
*
* Implementation for Bit-packing w1
*
* @param[in]:a-to be unpacked
* @param[out]:r-the result Poly.r
************************************/
void bit_unpacking_z(poly* r, uint8_t* a)
{
	int i;
	for (i = 0; i < Z_PACKSIZE / 9; ++i)
	{
		r->coff[4 * i + 0] = a[9 * i + 0];
		r->coff[4 * i + 0] |= (ssi_t)a[9 * i + 1] << 8;
		r->coff[4 * i + 0] |= (ssi_t)a[9 * i + 2] << 16;
		r->coff[4 * i + 0] &= 0x3FFFF;

		r->coff[4 * i + 1] = a[9 * i + 2] >> 2;
		r->coff[4 * i + 1] |= (ssi_t)a[9 * i + 3] << 6;
		r->coff[4 * i + 1] |= (ssi_t)a[9 * i + 4] << 14;
		r->coff[4 * i + 1] &= 0x3FFFF;

		r->coff[4 * i + 2] = a[9 * i + 4] >> 4;
		r->coff[4 * i + 2] |= (ssi_t)a[9 * i + 5] << 4;
		r->coff[4 * i + 2] |= (ssi_t)a[9 * i + 6] << 12;
		r->coff[4 * i + 2] &= 0x3FFFF;

		r->coff[4 * i + 3] = a[9 * i + 6] >> 6;
		r->coff[4 * i + 3] |= (ssi_t)a[9 * i + 7] << 2;
		r->coff[4 * i + 3] |= (ssi_t)a[9 * i + 8] << 10;
		r->coff[4 * i + 3] &= 0x3FFFF;

		r->coff[4 * i + 0] = GAMMA1 - r->coff[4 * i + 0];
		r->coff[4 * i + 1] = GAMMA1 - r->coff[4 * i + 1];
		r->coff[4 * i + 2] = GAMMA1 - r->coff[4 * i + 2];
		r->coff[4 * i + 3] = GAMMA1 - r->coff[4 * i + 3];
	}
}

/***********************************
*Func:bit_packing_t0
*
* Implementation for Bit-packing t0
*
* @param[in]:a-Poly.a to be packed
* @param[out]:r-the result
***********************************/
void bit_packing_t0(uint8_t* r, poly* a)
{
	int i;
	ssi_t temp[8];
	for (i = 0; i < T0_PACKSIZE / 13; ++i)
	{
		temp[0] = (1 << (D - 1)) - a->coff[8 * i + 0];
		temp[1] = (1 << (D - 1)) - a->coff[8 * i + 1];
		temp[2] = (1 << (D - 1)) - a->coff[8 * i + 2];
		temp[3] = (1 << (D - 1)) - a->coff[8 * i + 3];
		temp[4] = (1 << (D - 1)) - a->coff[8 * i + 4];
		temp[5] = (1 << (D - 1)) - a->coff[8 * i + 5];
		temp[6] = (1 << (D - 1)) - a->coff[8 * i + 6];
		temp[7] = (1 << (D - 1)) - a->coff[8 * i + 7];

		r[13 * i + 0] = temp[0];
		r[13 * i + 1] = temp[0] >> 8;
		r[13 * i + 1] |= temp[1] << 5;
		r[13 * i + 2] = temp[1] >> 3;
		r[13 * i + 3] = temp[1] >> 11;
		r[13 * i + 3] |= temp[2] << 2;
		r[13 * i + 4] = temp[2] >> 6;
		r[13 * i + 4] |= temp[3] << 7;
		r[13 * i + 5] = temp[3] >> 1;
		r[13 * i + 6] = temp[3] >> 9;
		r[13 * i + 6] |= temp[4] << 4;
		r[13 * i + 7] = temp[4] >> 4;
		r[13 * i + 8] = temp[4] >> 12;
		r[13 * i + 8] |= temp[5] << 1;
		r[13 * i + 9] = temp[5] >> 7;
		r[13 * i + 9] |= temp[6] << 6;
		r[13 * i + 10] = temp[6] >> 2;
		r[13 * i + 11] = temp[6] >> 10;
		r[13 * i + 11] |= temp[7] << 3;
		r[13 * i + 12] = temp[7] >> 5;
	}
}

/************************************
*Func:bit_unpacking_t0
*
* Implementation for Bit-unpacking t0
*
* @param[in]:a-to be unpacked
* @param[out]:r-the result Poly.r
************************************/
void bit_unpacking_t0(poly* r, uint8_t* a)
{
	int i;
	for (i = 0; i < T0_PACKSIZE / 13; ++i)
	{
		r->coff[8 * i + 0] = a[13 * i + 0] | (ssi_t)a[13 * i + 1] << 8 & 0x1FFF;
		r->coff[8 * i + 1] = a[13 * i + 1] >> 5 | (ssi_t)a[13 * i + 2] << 3 | (ssi_t)a[13 * i + 3] << 11 & 0x1FFF;
		r->coff[8 * i + 2] = a[13 * i + 3] >> 2 | (ssi_t)a[13 * i + 4] << 6 & 0x1FFF;
		r->coff[8 * i + 3] = a[13 * i + 4] >> 7 | (ssi_t)a[13 * i + 5] << 1 | (ssi_t)a[13 * i + 6] << 9 & 0x1FFF;
		r->coff[8 * i + 4] = a[13 * i + 6] >> 4 | (ssi_t)a[13 * i + 7] << 4 | (ssi_t)a[13 * i + 8] << 12 & 0x1FFF;
		r->coff[8 * i + 5] = a[13 * i + 8] >> 1 | (ssi_t)a[13 * i + 9] << 7 & 0x1FFF;
		r->coff[8 * i + 6] = a[13 * i + 9] >> 6 | (ssi_t)a[13 * i + 10] << 2 | (ssi_t)a[13 * i + 11] << 10 & 0x1FFF;
		r->coff[8 * i + 7] = a[13 * i + 11] >> 3 | (ssi_t)a[13 * i + 12] << 5 & 0x1FFF;

		r->coff[8 * i + 0] = (1 << (D - 1)) - r->coff[8 * i + 0];
		r->coff[8 * i + 1] = (1 << (D - 1)) - r->coff[8 * i + 1];
		r->coff[8 * i + 2] = (1 << (D - 1)) - r->coff[8 * i + 2];
		r->coff[8 * i + 3] = (1 << (D - 1)) - r->coff[8 * i + 3];
		r->coff[8 * i + 4] = (1 << (D - 1)) - r->coff[8 * i + 4];
		r->coff[8 * i + 5] = (1 << (D - 1)) - r->coff[8 * i + 5];
		r->coff[8 * i + 6] = (1 << (D - 1)) - r->coff[8 * i + 6];
		r->coff[8 * i + 7] = (1 << (D - 1)) - r->coff[8 * i + 7];
	}
}

/***********************************
*Func:bit_packing_t1
*
* Implementation for Bit-packing t1
*
* @param[in]:a-Poly.a to be packed
* @param[out]:r-the result
***********************************/
void bit_packing_t1(uint8_t* r, poly* a)
{
	int i;
	for (i = 0; i < T1_PACKSIZE / 5; ++i)
	{
		r[5 * i + 0] = a->coff[4 * i + 0];
		r[5 * i + 1] = a->coff[4 * i + 0] >> 8;
		r[5 * i + 1] |= a->coff[4 * i + 1] << 2;
		r[5 * i + 2] = a->coff[4 * i + 1] >> 6;
		r[5 * i + 2] |= a->coff[4 * i + 2] << 4;
		r[5 * i + 3] = a->coff[4 * i + 2] >> 4;
		r[5 * i + 3] |= a->coff[4 * i + 3] << 6;
		r[5 * i + 4] = a->coff[4 * i + 3] >> 2;
	}
}

/************************************
*Func:bit_unpacking_t1
*
* Implementation for Bit-unpacking t1
*
* @param[in]:a-to be unpacked
* @param[out]:r-the result Poly.r
************************************/
void bit_unpacking_t1(poly* r, uint8_t* a)
{
	int i;
	for (i = 0; i < T1_PACKSIZE / 5; ++i)
	{
		r->coff[4 * i + 0] = ((a[5 * i + 0]) | ((ssi_t)a[5 * i + 1] << 8)) & 0x3FF;
		r->coff[4 * i + 1] = ((a[5 * i + 1] >> 2) | ((ssi_t)a[5 * i + 2] << 6)) & 0x3FF;
		r->coff[4 * i + 2] = ((a[5 * i + 2] >> 4) | ((ssi_t)a[5 * i + 3] << 4)) & 0x3FF;
		r->coff[4 * i + 3] = ((a[5 * i + 3] >> 6) | ((ssi_t)a[5 * i + 4] << 2)) & 0x3FF;
	}
}

/***********************************
*Func:bit_packing_s
*
* Implementation for Bit-packing s
*
* @param[in]:a-Poly.a to be packed
* @param[out]:r-the result
***********************************/
void bit_packing_s(uint8_t* r, poly* a)
{
	int i;
	ssi_t temp[8];
	for (i = 0; i < S_PACKSIZE / 3; ++i)
	{
		temp[0] = ETA - a->coff[8 * i + 0];
		temp[1] = ETA - a->coff[8 * i + 1];
		temp[2] = ETA - a->coff[8 * i + 2];
		temp[3] = ETA - a->coff[8 * i + 3];
		temp[4] = ETA - a->coff[8 * i + 4];
		temp[5] = ETA - a->coff[8 * i + 5];
		temp[6] = ETA - a->coff[8 * i + 6];
		temp[7] = ETA - a->coff[8 * i + 7];

		r[3 * i + 0] = temp[0] | temp[1] << 3 | temp[2] << 6;
		r[3 * i + 1] = temp[2] >> 2 | temp[3] << 1 | temp[4] << 4 | temp[5] << 7;
		r[3 * i + 2] = temp[5] >> 1 | temp[6] << 2 | temp[7] << 5;
	}
}

/************************************
*Func:bit_unpacking_s
*
* Implementation for Bit-unpacking s
*
* @param[in]:a-to be unpacked
* @param[out]:r-the result Poly.r
************************************/
void bit_unpacking_s(poly* r, uint8_t* a)
{
	int i;
	for (i = 0; i < S_PACKSIZE / 3; ++i)
	{
		r->coff[8 * i + 0] = a[3 * i + 0] & 0x07;
		r->coff[8 * i + 1] = (a[3 * i + 0] >> 3) & 0x07;
		r->coff[8 * i + 2] = (a[3 * i + 0] >> 6) | (a[3 * i + 1] << 2) & 0x07;
		r->coff[8 * i + 3] = (a[3 * i + 1] >> 1) & 0x07;
		r->coff[8 * i + 4] = (a[3 * i + 1] >> 4) & 0x07;
		r->coff[8 * i + 5] = (a[3 * i + 1] >> 7) | (a[3 * i + 2] << 1) & 0x07;
		r->coff[8 * i + 6] = (a[3 * i + 2] >> 2) & 0x07;
		r->coff[8 * i + 7] = (a[3 * i + 2] >> 5) & 0x07;

		r->coff[8 * i + 0] = ETA - r->coff[8 * i + 0];
		r->coff[8 * i + 1] = ETA - r->coff[8 * i + 1];
		r->coff[8 * i + 2] = ETA - r->coff[8 * i + 2];
		r->coff[8 * i + 3] = ETA - r->coff[8 * i + 3];
		r->coff[8 * i + 4] = ETA - r->coff[8 * i + 4];
		r->coff[8 * i + 5] = ETA - r->coff[8 * i + 5];
		r->coff[8 * i + 6] = ETA - r->coff[8 * i + 6];
		r->coff[8 * i + 7] = ETA - r->coff[8 * i + 7];
	}
}

/**************************************
*Func:pk_packing
*
* Packing the public key:pk(rho||t1)
*
* @param[out]:pk-public key
* @param[in]:rho
* @param[in]:t1
**************************************/
void pk_packing(uint8_t pk[PK_SIZE], const uint8_t rho[SEEDBYTES], polyvctk* t1)
{
	int i;
	for (i = 0; i < SEEDBYTES; ++i)
	{
		pk[i] = rho[i];
	}
	pk += SEEDBYTES;

	for (i = 0; i < K; ++i)
	{
		bit_packing_t1(pk + i * T1_PACKSIZE, &t1->vctk[i]);
	}
}

/**************************************
*Func:pk_unpacking
*
* Unpacking the public key:pk(rho||t1)->rho,t1
*
* @param[in]:pk-public key
* @param[out]:rho
* @param[out]:t1
**************************************/
void pk_unpacking(uint8_t rho[SEEDBYTES], polyvctk* t1, const uint8_t* pk)
{
	int i;
	for (i = 0; i < SEEDBYTES; ++i)
	{
		rho[i] = pk[i];
	}
	pk += SEEDBYTES;

	for (i = 0; i < K; ++i)
	{
		bit_unpacking_t1(&t1->vctk[i], pk + i * T1_PACKSIZE);
	}
}

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
void sk_packing(uint8_t* sk, const uint8_t rho[SEEDBYTES], uint8_t key[SEEDBYTES], uint8_t tr[CRHBYTES], polyvctl* s1, polyvctk* s2, polyvctk* t0)
{
	int i;
	for (i = 0; i < SEEDBYTES; ++i)
	{
		sk[i] = rho[i];
	}
	sk += SEEDBYTES;

	for (i = 0; i < SEEDBYTES; ++i)
	{
		sk[i] = key[i];
	}
	sk += SEEDBYTES;

	for (i = 0; i < CRHBYTES; ++i)
	{
		sk[i] = tr[i];
	}
	sk += CRHBYTES;

	for (i = 0; i < L; ++i)
	{
		bit_packing_s(sk + i * S_PACKSIZE, &s1->vctl[i]);
	}
	sk += L * S_PACKSIZE;

	for (i = 0; i < K; ++i)
	{
		bit_packing_s(sk + i * S_PACKSIZE, &s2->vctk[i]);
	}
	sk += K * S_PACKSIZE;

	for (i = 0; i < K; ++i)
	{
		bit_packing_t0(sk + i * T0_PACKSIZE, &t0->vctk[i]);
	}
}

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
void sk_unpacking(uint8_t rho[SEEDBYTES], uint8_t key[SEEDBYTES], uint8_t tr[CRHBYTES], polyvctl* s1, polyvctk* s2, polyvctk* t0, const uint8_t* sk)
{
	int i;
	for (i = 0; i < SEEDBYTES; ++i)
	{
		rho[i] = sk[i];
	}
	sk += SEEDBYTES;

	for (i = 0; i < SEEDBYTES; ++i)
	{
		key[i] = sk[i];
	}
	sk += SEEDBYTES;

	for (i = 0; i < CRHBYTES; ++i)
	{
		tr[i] = sk[i];
	}
	sk += CRHBYTES;

	for (i = 0; i < L; ++i)
	{
		bit_unpacking_s(&s1->vctl[i], sk + i * S_PACKSIZE);
	}
	sk += L * S_PACKSIZE;

	for (i = 0; i < K; ++i)
	{
		bit_unpacking_s(&s2->vctk[i], sk + i * S_PACKSIZE);
	}
	sk += K * S_PACKSIZE;

	for (i = 0; i < K; ++i)
	{
		bit_unpacking_t0(&t0->vctk[i], sk + i * T0_PACKSIZE);
	}
}

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
void sig_packing(uint8_t sig[SIG_SIZE], const polyvctl* z, const polyvctk* h, const uint8_t c[SEEDBYTES])
{
	int i, j, k = 0;
	for (i = 0; i < SEEDBYTES; ++i)
	{
		sig[i] = c[i];
	}
	sig += SEEDBYTES;

	for (i = 0; i < L; ++i)
	{
		bit_packing_z(sig + i * Z_PACKSIZE, &z->vctl[i]);
	}
	sig += L * Z_PACKSIZE;
	/*for (i = 0; i < L * Z_PACKSIZE; ++i)
		printf("%d ", sig[i]);*/
	for (i = 0; i < OMEGA + K; ++i)
	{
		sig[i] = 0;
	}

	for (i = 0; i < K; ++i)
	{
		for (j = 0; j < N; ++j)
		{
			if (h->vctk[i].coff[j] != 0)
				sig[k++] = j;//前omega byte记录h中非零的系数位置
		}
		sig[OMEGA + i] = k;
	}
}

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
int sig_unpacking(polyvctl* z, polyvctk* h, uint8_t c[SEEDBYTES], const uint8_t sig[SIG_SIZE])
{
	int i, j, k = 0;
	for (i = 0; i < SEEDBYTES; ++i)
	{
		c[i] = sig[i];
	}
	sig += SEEDBYTES;

	for (i = 0; i < L; ++i)
	{
		bit_unpacking_z(&z->vctl[i], sig + i * Z_PACKSIZE);
	}
	sig += L * Z_PACKSIZE;

	for (i = 0; i < K; ++i)
	{
		for (j = 0; j < N; ++j)
		{
			h->vctk[i].coff[j] = 0;
		}
		/*printf("%d\n", sig[OMEGA + i]);*/
		if (sig[OMEGA + i]<k || sig[OMEGA + i]>OMEGA)
			return 1;
		for (j = k; j < sig[OMEGA + i]; ++j)
		{
			if (j > k && sig[j] <= sig[j - 1])
				return 1;
			h->vctk[i].coff[sig[j]] = 1;
		}
		k = sig[OMEGA + i];
	}
	return 0;
}