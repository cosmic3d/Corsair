#include "../corsair.h"

int decrypt_str(t_global2 *g)
{
    char buffer[1000];
    int i;
    FILE *fp;
	RSA *rsa;

	fp = fopen("pems/private.pem", "r");
	rsa = RSA_new();
	rsa = PEM_read_RSAPrivateKey(fp, &rsa, NULL, NULL);
	fclose(fp);
	if(rsa == NULL)
	{
		printf("\n\n%s\n\n", "ERROR READING PRIVATE KEY");
		return (-1);
	}
	printf("\n\nThe string you want to decrypt is: \n----\n%s\n----\n", g->encrypted_message);
    i = RSA_private_decrypt(RSA_size(rsa), (unsigned char *)g->encrypted_message, (unsigned char *)buffer, rsa, RSA_PKCS1_PADDING);
    if (i == -1)
	{
		printf("\n\n%s\n\n", "ERROR CREATING DECRYPTED MESSAGE");
		return (i);
	}
	printf("\n\nThe decrypted string is: \n----\n%s\n----\n", buffer);
	printf("\n\nThe size in bytes is: \n----\n%i\n----\n", i);
	RSA_free(rsa);
    return(i);
}