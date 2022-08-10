#include "../corsair.h"

int encrypt_str(char *c, t_global2 *g)
{
	char buffer[1000];
	int i = 0;
	FILE *fp;
	RSA *rsa;

	fp = fopen("pems/public.pem", "r");
	rsa = RSA_new();
	rsa = PEM_read_RSA_PUBKEY(fp, &rsa, NULL, NULL);
	if(rsa == NULL)
	{
		red();
		printf("\n\n%s\n\n", "ERROR READING PUBLIC KEY");
		reset();
		return (-1);
	}
	//write(1, "\nAAqui lliga\n", 13);
	while (c[i] != '\0')
		i++;
	//  int RSA_public_encrypt(int flen, const unsigned char *from,
    // unsigned char *to, RSA *rsa, int padding);
	//write(1, "\nAAqui llega\n", 13);
	i = RSA_public_encrypt(i, (unsigned char *)c, (unsigned char *)buffer, rsa, RSA_PKCS1_PADDING);
	//write(1, "\nAAqui llega\n", 13);
	if (i == -1)
	{
		red();
		printf("\n\n%s\n\n", "ERROR CREATING ENCRYPTED MESSAGE");
		reset();
		return (i);
	}
	printf("\n\nThe string you want to encrypt is: \n----\n%s\n----\n", c);
	printf("\n\nThe encrypted string is: \n----\n%s\n----\n", buffer);
	printf("\n\nThe size in bytes is: \n----\n%i\n----\n", i);
	g->encrypted_message = buffer;
	g->len_encrypted = i;
	printf("\n\nThe encryptedmessage is: \n----\n%s\n----\n", g->encrypted_message);
	printf("\n\nThe len_encrypted is: \n----\n%i\n----\n", g->len_encrypted);
	return (i);
}