setran(struct csa *csa, int iseed)
{     xassert(iseed >= 1);
      mult = 16807;
      modul = 2147483647;
      i15 = 1 << 15;
      i16 = 1 << 16;
      jran = iseed;
      return;
}
