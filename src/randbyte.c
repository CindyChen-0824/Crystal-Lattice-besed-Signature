#include "../inc/randbyte.h"
#include "../inc/deftype.h"
/*********************************************
*Func:rand_byte
*
* Generate random bytes for r_len
*
* @param[out]:r_byte-random bytes
* @param[in]:r_len-the length of r_byte
*********************************************/
void rand_byte(uint8_t* r_byte, size_t r_len)
{
	HCRYPTPROV ctx;
	size_t len;

	if((CryptAcquireContext(&ctx,NULL,NULL,PROV_RSA_FULL,CRYPT_VERIFYCONTEXT)==0))
		abort();

	while (r_len > 0)
	{
		len = (r_len > RANDLIM) ? RANDLIM : r_len;
		if (CryptGenRandom(ctx, len, (BYTE*)r_byte) == 0)
			abort();

		r_byte += len;
		r_len -= len;
	}
}