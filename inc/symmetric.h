#ifndef SYMMETRIC_H
#define SYMMETRIC_H

#include "../inc/fips202.h"
#include "../inc/deftype.h"

#define STREAM128_BLOCKBYTES SHAKE128_RATE//168
#define STREAM256_BLOCKBYTES SHAKE256_RATE//136

typedef keccak_state stream128_state;
typedef keccak_state stream256_state;

void shake128_stream_init(keccak_state* state, uint8_t seed[SEEDBYTES], ssi_t nonce);

void shake256_stream_init(keccak_state* state, uint8_t seed[CRHBYTES], ssi_t nonce);

#endif // !SYMMETRIC_H
