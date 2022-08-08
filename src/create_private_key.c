#include "../corsair.h"

// BN_div divides |numerator| by |divisor| and places the result in |quotient|
// and the remainder in |rem|. Either of |quotient| or |rem| may be NULL, in
// which case the respective value is not returned. The result is rounded
// towards zero; thus if |numerator| is negative, the remainder will be zero or
// negative. It returns one on success or zero on error.
//OPENSSL_EXPORT int BN_div(BIGNUM *quotient, BIGNUM *rem,
//                          const BIGNUM *numerator, const BIGNUM *divisor,
//                          BN_CTX *ctx);

int get_q(t_global *g)
{
  BN_CTX *ctx = BN_CTX_new ();

  if (BN_div(g->vars.q, NULL, g->vars.n, g->gcd, ctx) == 0)
  {
    red();
    printf("\nThe division: N/Q has failed\n");
    reset();
    return (-1);
  }
  green();
  printf("\nP = %s\n", BN_bn2dec(g->gcd));
  printf("\nQ = %s\n", BN_bn2dec(g->vars.q));
  printf("\n\nWe can begin creating the private key!\n\n");
  reset();
  return (0);
}

int cpk(char *_p, char *_q)
{
  FILE   *fp;
  BIGNUM *n = BN_new ();
  BIGNUM *d = BN_new ();
  BIGNUM *e = BN_new ();
  BIGNUM *p = BN_new ();
  BIGNUM *q = BN_new ();
  BIGNUM *p1 = BN_new ();
  BIGNUM *q1 = BN_new ();
  BIGNUM *dmp1 = BN_new ();
  BIGNUM *dmq1 = BN_new ();
  BIGNUM *iqmp = BN_new ();
  BIGNUM *phi = BN_new ();
  BN_CTX *ctx = BN_CTX_new ();
  RSA *key = RSA_new ();

  if (!(BN_dec2bn (&p, (const char *)_p)) || !(BN_dec2bn (&q, (const char *)_q))) {
      fprintf (stderr, "\nERROR SETTING P AND Q\n");
      exit (1);
  }

  if (!(BN_is_prime_ex (p, BN_prime_checks, ctx, NULL)) ||
      !(BN_is_prime_ex (q, BN_prime_checks, ctx, NULL))) {
      fprintf (stderr, "ERROR: Arguments must both be prime!\n");
      exit (1);
  }

  BN_dec2bn (&e, "65537");

  /* Calculate RSA private key parameters */

  /* n = p*q */
  BN_mul (n, p, q, ctx);
  /* p1 = p-1 */
  BN_sub (p1, p, BN_value_one ());
  /* q1 = q-1 */
  BN_sub (q1, q, BN_value_one ());
  /* phi(pq) = (p-1)*(q-1) */
  BN_mul (phi, p1, q1, ctx);
  /* d = e^-1 mod phi */
  BN_mod_inverse (d, e, phi, ctx);
  /* dmp1 = d mod (p-1) */
  BN_mod (dmp1, d, p1, ctx);
  /* dmq1 = d mod (q-1) */
  BN_mod (dmq1, d, q1, ctx);
  /* iqmp = q^-1 mod p */
  BN_mod_inverse (iqmp, q, p, ctx);

  /* Populate key data structure using RSA_set0 accessor methods */
  RSA_set0_key(key, n, e, d);
  RSA_set0_factors(key, p, q);
  RSA_set0_crt_params(key, dmp1, dmq1, iqmp);

  if (RSA_check_key(key) != 1) {
    printf("OpenSSL reports internal inconsistency in generated RSA key!\n");
    exit(1);
  }

  /* Output the private key in human-readable and PEM forms */
  //RSA_print_fp (stdout, key, 5);
  printf("\n");
  PEM_write_RSAPrivateKey (stdout, key, NULL, NULL, 0, 0, NULL);
  /* Write the private key to .pem file in pems directory */
  fp = fopen("pems/private.pem", "w");
	PEM_write_RSAPrivateKey(fp, key, NULL, NULL, NULL, NULL, NULL);
	fclose(fp);
  /* Release allocated objects */
  BN_CTX_free (ctx);
  RSA_free(key); /* also frees n, e, d, p, q, dmp1, dmq1, iqmp */
  BN_clear_free (phi);
  BN_clear_free (p1);
  BN_clear_free (q1);
}