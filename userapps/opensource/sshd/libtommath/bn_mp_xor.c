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

/* XOR two ints together */
int
mp_xor (mp_int * a, mp_int * b, mp_int * c)
{
  int     res, ix, px;
  mp_int  t, *x;

  if (a->used > b->used) {
    if ((res = mp_init_copy (&t, a)) != MP_OKAY) {
      return res;
    }
    px = b->used;
    x = b;
  } else {
    if ((res = mp_init_copy (&t, b)) != MP_OKAY) {
      return res;
    }
    px = a->used;
    x = a;
  }

  for (ix = 0; ix < px; ix++) {
    t.dp[ix] ^= x->dp[ix];
  }
  mp_clamp (&t);
  mp_exch (c, &t);
  mp_clear (&t);
  return MP_OKAY;
}
