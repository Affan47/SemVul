__asinl (long double x)
{
  if (__builtin_expect (isgreater (fabsl (x), 1.0L), 0)
      && _LIB_VERSION != _IEEE_)
    {

      feraiseexcept (FE_INVALID);
      return __kernel_standard_l (x, x, 202);
    }

  return __ieee754_asinl (x);
}
