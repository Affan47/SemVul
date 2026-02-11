s_mp_ispow2d(mp_digit d)
{
  if ((d != 0) && ((d & (d-1)) == 0)) {
    int pow = 0;
#if defined (MP_USE_UINT_DIGIT)
    if (d & 0xffff0000U)
      pow += 16;
    if (d & 0xff00ff00U)
      pow += 8;
    if (d & 0xf0f0f0f0U)
      pow += 4;
    if (d & 0xccccccccU)
      pow += 2;
    if (d & 0xaaaaaaaaU)
      pow += 1;
#elif defined(MP_USE_LONG_LONG_DIGIT)
    if (d & 0xffffffff00000000ULL)
      pow += 32;
    if (d & 0xffff0000ffff0000ULL)
      pow += 16;
    if (d & 0xff00ff00ff00ff00ULL)
      pow += 8;
    if (d & 0xf0f0f0f0f0f0f0f0ULL)
      pow += 4;
    if (d & 0xccccccccccccccccULL)
      pow += 2;
    if (d & 0xaaaaaaaaaaaaaaaaULL)
      pow += 1;
#elif defined(MP_USE_LONG_DIGIT)
    if (d & 0xffffffff00000000UL)
      pow += 32;
    if (d & 0xffff0000ffff0000UL)
      pow += 16;
    if (d & 0xff00ff00ff00ff00UL)
      pow += 8;
    if (d & 0xf0f0f0f0f0f0f0f0UL)
      pow += 4;
    if (d & 0xccccccccccccccccUL)
      pow += 2;
    if (d & 0xaaaaaaaaaaaaaaaaUL)
      pow += 1;
#else
#error "unknown type for mp_digit"
#endif
    return pow;
  }
  return -1;

}
