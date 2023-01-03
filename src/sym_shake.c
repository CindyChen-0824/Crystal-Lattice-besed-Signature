#include "../inc/fips202.h"
#include "../inc/symmetric.h"
#include "../inc/system_para.h"
#include "../inc/deftype.h"

void shake128_stream_init(keccak_state* state, uint8_t seed[SEEDBYTES], ssi_t nonce)
{
	uint8_t t[2];//´æ·Å16bitµÄnonce
	t[0] = nonce;
	t[1] = nonce >> 8;

	shake128_init(state);
	shake128_absorb(state, seed, SEEDBYTES);
	shake128_absorb(state, t, 2);
	shake128_finalize(state);
}

void shake256_stream_init(keccak_state* state, uint8_t seed[CRHBYTES], ssi_t nonce)
{
	uint8_t t[2];
	t[0] = nonce;
	t[1] = nonce >> 8;

	shake256_init(state);
	shake256_absorb(state, seed, CRHBYTES);
	shake256_absorb(state, t, 2);
	shake256_finalize(state);
}