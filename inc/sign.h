#ifndef SIGN_H
#define SIGN_H

#include<stdint.h>

/***************************************
*Func:KeyGen
*
* Generate public key and secrete key.
* Returns 0 if success.
*
* @param[out]:pk
* @param[out]:sk
***************************************/
int KeyGen(uint8_t* pk, uint8_t* sk);

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
int Sign(uint8_t* sk, const uint8_t* M, size_t Mlen, uint8_t* sig, size_t siglen);

int Signing(uint8_t* sm, size_t smlen, const uint8_t* m, size_t mlen, const uint8_t* sk);

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
int Verify(const uint8_t* pk, const uint8_t* M, size_t Mlen, const uint8_t* sig, size_t siglen);
#endif // !SIGN_H