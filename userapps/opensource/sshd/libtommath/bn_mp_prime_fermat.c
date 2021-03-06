/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is library that provides for multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library is designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tomstdenis@iahu.ca, http://math.libtomcrypt.org
 */
#include <tommath.h>

/* performs one Fermat test.
 * 
 * If "a" were prime then b^a == b (mod a) since the order of
 * the multiplicative sub-group would be phi(a) = a-1.  That means
 * it would be the same as b^(a mod (a-1)) == b^1 == b (mod a).
 *
 * Sets result to 1 if the congruence holds, or zero otherwise.
 */
int
mp_prime_fermat (mp_int * a, mp_int * b, int *result)
{
  mp_int  t;
  int     err;

  /* default to fail */
  *result = 0;

  /* init t */
  if ((err = mp_init (&t)) != MP_OKAY) {
    return err;
  }

  /* compute t = b^a mod a */
  if ((err = mp_exptmod (b, a, a, &t)) != MP_OKAY) {
    goto __T;
  }

  /* is it equal to b? */
  if (mp_cmp (&t, b) == MP_EQ) {
    *result = 1;
  }

  err = MP_OKAY;
__T:mp_clear (&t);
  return err;
}
