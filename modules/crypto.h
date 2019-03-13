#ifndef __CROSS_CMD_CRYPTO_H__
#define __CROSS_CMD_CRYPTO_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* crypto_encrypt(const char* plain_text, char key)
{
	/*
	*	@todo: simple encrypt a plaintext message.
	*	@plain_text: plain text ecrypted
	*	@key: key to encrypt.
	*/
	int len = strlen(plain_text);
	char* en_text = (char*)malloc(len + 1);
	int i = 0;
	for (i = 0; i < len; ++i)
		en_text[i] = plain_text[i] ^ key;
	en_text[i] = '\0';
	return en_text;
}

char* crypto_decrypt(const char* plain_text, char key)
{
	return crypto_encrypt(plain_text, key);
}

#endif	// __CROSS_CMD_CRYPTO_H__