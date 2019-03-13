#include "../modules/crypto.h"

#define KEY 11

int main(int argc, char const *argv[])
{
	char* plain_text = "1234567890qwertyuiopadsfghjklzcxvbnmZXCVBNMASDFGHJKLQWERTYUIOP`~!@#$%^&*()-=_+[]{}\\|;:'\",<.>/?";
	char* en_text = crypto_encrypt(plain_text, KEY);
	char* de_text = crypto_decrypt(en_text, KEY);
	printf("Plain text    : %s\n", plain_text);
	printf("Encrypted text: %s\n", en_text);
	printf("Decrypted text: %s\n", de_text);
	return 0;
}