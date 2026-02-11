j0f (float x)
{
  if (__builtin_expect (isgreater (fabsf (x), (float) X_TLOSS), 0)
      && _LIB_VERSION != _IEEE_ && _LIB_VERSION != _POSIX_)

    return __kernel_standard_f (x, x, 134);

  return __ieee754_j0f (x);
}
