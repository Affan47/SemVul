rgba_to_lchab (char *src,
               char *dst,
               long  n)
{
  while (n--)
    {
      double red   = ((double *) src)[0];
      double green = ((double *) src)[1];
      double blue  = ((double *) src)[2];
      double L, a, b, C, H;

      cpercep_rgb_to_space (red, green, blue, &L, &a, &b);
      ab_to_chab (a, b, &C, &H);

      ((double *) dst)[0] = L;
      ((double *) dst)[1] = C;
      ((double *) dst)[2] = H;

      src += sizeof (double) * 4;
      dst += sizeof (double) * 3;
    }
  return n;
}
