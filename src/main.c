#include<stdio.h>
#include<stdlib.h>
#include "../inc/deftype.h"
#include "../inc/system_para.h"
#include "../inc/rounding.h"
#include "../inc/sign.h"
//#include "../inc/randbyte.h"

#define MLEN 59
#define TESTNUM 1000
int main()
{
	size_t i, j;
	int ret = 0;
	size_t mlen = MLEN, smlen = SIG_SIZE;
	size_t b;
	uint8_t m[MLEN] = { 0 };
	uint8_t m2[MLEN + SIG_SIZE];
	uint8_t sm[MLEN + SIG_SIZE] = { 0 };
	uint8_t pk[PK_SIZE];
	uint8_t sk[SK_SIZE];

	for (j = 0; j < TESTNUM; j++)
	{
		rand_byte(m, MLEN);

		KeyGen(pk, sk);

		for (i = 0; i < mlen; ++i)
		{
			sm[SIG_SIZE + mlen - 1 - i] = m[mlen - 1 - i];
		}
		Sign(sk, m, MLEN, sm, SIG_SIZE);
		smlen += MLEN;

		mlen = smlen - SIG_SIZE;
		ret = Verify(pk, sm + SIG_SIZE, mlen, sm, SIG_SIZE);

		printf("%d\n", ret);
		if (ret != 0)
		{
			printf("Wrong!\n");
			return 0;
		}
		smlen = SIG_SIZE;
	}
	printf("All Pass!\n");
	
	system("pause");

	return 0;
}