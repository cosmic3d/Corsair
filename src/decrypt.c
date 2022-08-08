#include "../corsair.h"

int decrypt(char c)
{
	BN_CTX *ctx = BN_CTX_new();
	FILE   *fp;
  	BIGNUM *n = BN_new ();
  	BIGNUM *e = BN_new ();
	BIGNUM *r = BN_new ();
	BIGNUM *square = BN_new ();
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
	n = RSA_get0_n(rsa);
	e = RSA_get0_e(rsa);
	if (BN_dec2bn(&r, "j") == 0)
	{
		red();
		printf("\n\nERROR PASSING CHAR TO BIGNUM: %c\n\n", c);
		reset();
		return (-1);
	}
	if (BN_exp(square, r, e, ctx) == 0)
	{
    	red();
    	printf("\nThe exponentiation has failed\n");
    	reset();
    	return (-1);
  	}
	if (BN_div(NULL, r, square, n, ctx) == 0)
  	{
    	red();
    	printf("\nThe division has failed\n");
    	reset();
    	return (-1);
  	}
	green();
	printf("\nThe exponent number is: %s\n", BN_bn2dec(e));
	printf("\nThe modulus number is: %s\n", BN_bn2dec(n));
	printf("\nThe original number is: %i\n", (int)c);
	printf("\nThe remainder is: %s\n", BN_bn2dec(r));
	reset();
	return (0);
}