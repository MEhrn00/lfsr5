#ifndef LFSRCRYPTO_H_INCLUDED
#define LFSRCRYPTO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void gen_key(uint8_t* key,char seed[5], long size);

void encrypt_data(char* data, uint8_t* key, long size);

#endif
