#include "../corsair.h"

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
int		euclides_shit(t_global *g, char *i, char *j)
{
	BN_CTX *ctx = BN_CTX_new();
	char *gcd;
	char *n;
	char *n2;
	
	if (BN_gcd(g->gcd, g->vars.n, g->vars2.n, ctx) == 0)
	{
		red();
		printf("\nThe gcd between %s and %s has failed\n", i, j);
		reset();
		BN_CTX_free (ctx);
		return (-1);
	}
	n = BN_bn2dec(g->vars.n);
	n2 = BN_bn2dec(g->vars2.n);
	if (strcmp(n, n2) == 0)
	{
		yellow();
		printf("\n%s and %s are the same\n", i, j);
		reset();
		BN_CTX_free (ctx);
		free(n);
		free(n2);
		return (0);
	}
	gcd = BN_bn2dec(g->gcd);
	printf("\nGCD is: %s\n", gcd);
	if (strcmp(gcd, "1") == 0)
	{
		yellow();
		printf("\nThe gcd between %s and %s is 1\n", i, j);
		reset();
		BN_CTX_free (ctx);
		free(n);
		free(n2);
		free(gcd);
		return (0);
	}
	else
	{
		green();
		printf("\nThe gcd between %s and %s is:\n%s\n\nThe exploit may begin\n", i, j, gcd);
		reset();
		g->vars.factor_found = 1;
		g->vars2.factor_found = 1;
		BN_CTX_free (ctx);
		free(n);
		free(n2);
		free(gcd);
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
	FILE *fp2;
	RSA *rsa;
	BIGNUM *n;
	BIGNUM *e;
	
	fp = fopen(w, "r");
	if (!fp)
	{
		red();
		printf("\nERROR READING FILES: \n%s\n", w);
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
		RSA_free(rsa);
		return (-1);
	}
	fclose(fp);
	fp2 = fopen("pems/public.pem", "w");
	PEM_write_RSA_PUBKEY(fp2, rsa);
	fclose(fp2);
	n = RSA_get0_n(rsa);
	e = RSA_get0_e(rsa);
	if (i == 0)
	{
		g->vars.n = BN_dup(n);
		g->vars.e = BN_dup(e);
		RSA_free(rsa);
		return (0);
	}
	g->vars2.n = BN_dup(n);
	g->vars2.e = BN_dup(e);
	RSA_free(rsa);//Dont worry, this also frees all the other values in the involved operations(n and e)
	return (0);
}

int	print_ne(t_global *g, char *i, char *j)
{
	char *n;
	char *e;
	char *n2;
	char *e2;

	n = BN_bn2dec(g->vars.n);
	e = BN_bn2dec(g->vars.e);
	n2 = BN_bn2dec(g->vars2.n);
	e2 = BN_bn2dec(g->vars2.e);
	green();
	printf("\n-----%s-----\n", i);
	reset();
	printf("\nModulus: %s\n\nExponent: %s\n\n", n, e);
	green();
	printf("\n-----%s-----\n", j);
	reset();
	printf("\nModulus: %s\n\nExponent: %s\n\n", n2, e2);

	free(n);
	free(e);
	free(n2);
	free(e2);
	return(0);
}