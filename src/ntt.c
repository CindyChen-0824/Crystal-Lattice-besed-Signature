#include "../inc/ntt.h"

/*****************************************
* Func:ntt
*
* Forward NTT(CT)
* Output in bitreversed order
*
* @param:*a-coefficients array
******************************************/
void ntt(ssi_t* a)
{
	int k = 1;
	int len, start, j = 0;
	ssi_t t;
	for (len = N / 2; len > 0; len >>= 1)
	{
		for (start = 0; start < N; start = j + len)
		{
			for (j = start; j < start + len; j++)
			{
				t = mont_rdc((sdi_t)omega[k] * a[j + len]);
				a[j + len] = a[j] - t;//×ó×ÓÊ÷
				a[j] = a[j] + t;//ÓÒ×ÓÊ÷
			}
			k++;
		}
	}
}

/*****************************************
* Func:invntt(GS)
*
* Inverse NTT in Montgomery Form
* Output results in Z_q
*
* @param:*a-coefficients array
******************************************/
void invntt_tomont(ssi_t* a)
{
	int k = N - 1;
	int len, start, j;
	//int zeta;
	ssi_t t;
	int F = 41978; //MONTFCT^2/256 % Q

	for (len = 1; len < N; len <<= 1)
	{
		for (start = 0; start < N; start = j + len)
		{
			for (j = start; j < start + len; ++j)
			{
				t = a[j];
				a[j] = t + a[j + len];
				a[j + len] = mont_rdc((t - a[j + len]) * (sdi_t)(-omega[k]));
				/*zeta = -omega[k];*/
			}
			k--;
		}
	}

	for (int i = 0; i < N; ++i)
	{
		a[i] = mont_rdc((sdi_t)F * a[i]);
	}
}
