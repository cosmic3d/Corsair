#include "corsair.h"

void red () 
{
  printf("\033[1;31m");
}

void yellow ()
{
  printf("\033[1;33m");
}

void reset () 
{
  printf("\033[0m");
}

void green ()
{
  printf("\033[0;32m");
}

// BN_gcd sets |r| = gcd(|a|, |b|). It returns one on success and zero
// otherwise.
//OPENSSL_EXPORT int BN_gcd(BIGNUM *r, const BIGNUM *a, const BIGNUM *b,
//                          BN_CTX *ctx);
int		euclides_shit(t_global *g, char *i, char *j)
{
	BN_CTX *ctx = BN_CTX_new();
	
	if (BN_gcd(g->gcd, g->vars.n, g->vars2.n, ctx) == 0)
	{
		red();
		printf("\nThe gcd between %s and %s has failed\n", i, j);
		reset();
		return (-1);
	}
	if (g->vars.n == g->vars2.n)
	{
		//printf("\nvars is: %s\n\nvars2 is %s\n", BN_bn2dec(g->vars.n), BN_bn2dec(g->vars2.n));
		yellow();
		printf("\n%s and %s are the same\n", i, j);
		reset();
		return (0);
	}
	printf("\nGCD is: %s\n", BN_bn2dec(g->gcd));
	if (strcmp(BN_bn2dec(g->gcd), "1") == 0)
	{
		yellow();
		printf("\nThe gcd between %s and %s is 1\n", i, j);
		reset();
		return (0);
	}
	else
	{
		green();
		printf("\nThe gcd between %s and %s is:\n%s\n\nThe exploit may begin\n", i, j, BN_bn2dec(g->gcd));
		reset();
		g->vars.factor_found = 1;
		g->vars2.factor_found = 1;
		return (0);
	}
}

int		error_args(int argc, char **pems)
{
	if (argc <= 2)
	{
		red();
		printf("\nERROR: Not enough arguments. I need at least 2 certificates to try to exploit the RSA algorithm\n");
		reset();
		return (-1);
	}
	return (0);
}

int	set_ne(t_global *g, char *w, int i)//MODIFICAR PARA T_VARS
{
	FILE *fp;
	RSA *rsa;

	fp = fopen(w, "r");
	if (!fp)
	{
		red();
		printf("\nERROR READING FILES: \n%s\n%s\n", w);
		reset();
		return (-1);
	}
	rsa = RSA_new();
	rsa = PEM_read_RSA_PUBKEY(fp, &rsa, NULL, NULL);
	if(rsa == NULL)
	{
		red();
		printf("\n\n%s\n\n", "ERROR READING PUBLIC KEY");
		reset();
		return (-1);
	}
	fclose(fp);
	if (i == 0)
	{
		g->vars.n = RSA_get0_n(rsa);
		g->vars.e = RSA_get0_e(rsa);
		return (0);
	}
	g->vars2.n = RSA_get0_n(rsa);
	g->vars2.e = RSA_get0_e(rsa);
	return (0);
}

int	print_ne(t_global *g, char *i, char *j)
{
	green();
	printf("\n-----%s-----\n", i);
	reset();
	printf("\nExponent: %s\n\nModulus: %s\n\n", BN_bn2dec(g->vars.n), BN_bn2dec(g->vars.e));
	green();
	printf("\n-----%s-----\n", j);
	reset();
	printf("\nExponent: %s\n\nModulus: %s\n\n", BN_bn2dec(g->vars2.n), BN_bn2dec(g->vars2.e));
	return(0);
}
