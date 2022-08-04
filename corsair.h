#ifndef CORSAIR_H
# define CORSAIR_H

#include <math.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/pem2.h>
#include <openssl/bn.h>
#include <openssl/bio.h>
#include <openssl/opensslv.h>
#include <openssl/engine.h>

typedef struct s_vars
{
    int     factor_found;
	BIGNUM  *p;
    BIGNUM  *q;
    BIGNUM  *e;
    BIGNUM  *n;
}               t_vars;

typedef struct s_global
{
    t_vars  vars;
    t_vars  vars2;
    BIGNUM  *gcd;
}               t_global;

void red ();
void yellow ();
void reset ();
void green (); 
int		euclides_shit(t_global *g, char *i, char *j);
int		error_args(int argc, char **pems);
int	set_ne(t_global *g, char *w, int i);
int	print_ne(t_global *g, char *i, char *j);
#endif