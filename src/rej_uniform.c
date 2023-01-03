#include "../inc/rej_uniform.h"

/***************************************************
*Func:rej_uni
* Perform rejection sampling for coefficients in[0,Q-1]
*
* @param[in]:a-poly.a
* @param[in]:len-length of a
* @param[in]:buf-array of random bytes
* @param[in]:buflen-length of buf
***************************************************/
int rej_uni(ssi_t* a, int len, uint8_t* buf, int buflen)
{
	int ctr = 0, pos = 0;
	ssi_t t;

	while (ctr < len && pos + 3 <= buflen)
	{
		t = buf[pos++];
		t |= (ssi_t)buf[pos++] << 8;
		t |= (ssi_t)buf[pos++] << 16;
		t &= QBTMASK;

		if (t < Q)
			a[ctr++] = t;
	}

	return ctr;
}

/***************************************************
*Func:rej_eta
* Perform rejection sampling for coefficients in [-eta,eta]
*
* @param[in]:a-poly.a
* @param[in]:len-length of a
* @param[in]:buf-array of random bytes
* @param[in]:buflen-length of buf
***************************************************/
int rej_eta(ssi_t* a, int len, uint8_t* buf, int buflen)
{
	int ctr = 0, pos = 0;
	ssi_t t0, t1;

	while (ctr < len && pos < buflen)
	{
		t0 = buf[pos] & 0x0F;//È¡buf-arrayµÍ4Î»
		t1 = buf[pos++] >> 4;

		if (t0 < 15)
		{
			t0 = t0 - (205 * t0 >> 10) * 5;
			a[ctr++] = ETA - t0;
		}
		if (t1 < 15 && ctr < len)
		{
			t1 = t1 - (205 * t1 >> 10) * 5;
			a[ctr++] = ETA - t1;
		}
	}

	return ctr;
}