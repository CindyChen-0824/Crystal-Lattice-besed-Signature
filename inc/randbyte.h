#ifndef RANDBYTE_H
#define RANDBYTE_H

#include <stddef.h>
#include <stdlib.h>
#include <Windows.h>
#include <wincrypt.h>
#include <stdint.h>
//#include "../inc/system_para.h"

/*********************************************
*Func:rand_byte
* 
* Generate random bytes for r_len
* 
* @param[out]:r_byte-random bytes
* @param[in]:r_len-the length of r_byte
*********************************************/
void rand_byte(uint8_t* r_byte, size_t r_len);
#endif // !RANDBYTE_H
