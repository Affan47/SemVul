_scryptBlockMix (u32 r, unsigned char *B, unsigned char *tmp2)
{
  u64 i;
  unsigned char *X = tmp2;
  unsigned char *Y = tmp2 + 64;

#if 0
  if (r == 1)
    {
      for (i = 0; i < 2 * r; i++)
        {
          size_t j;
          printf ("B[%d] = ", (int)i);
          for (j = 0; j < 64; j++)
            {
              if (j && !(j % 16))
                printf ("\n       ");
              printf (" %02x", B[i * 64 + j]);
            }
          putchar ('\n');
        }
    }
#endif


  memcpy (X, &B[(2 * r - 1) * 64], 64);


  for (i = 0; i <= 2 * r - 1; i++)
    {

      buf_xor(X, X, &B[i * 64], 64);


      _salsa20_core ((u32*)X, (u32*)X, 8);


      memcpy (&Y[i * 64], X, 64);
    }

  for (i = 0; i < r; i++)
    {
      memcpy (&B[i * 64], &Y[2 * i * 64], 64);
      memcpy (&B[(r + i) * 64], &Y[(2 * i + 1) * 64], 64);
    }

#if 0
  if (r==1)
    {
      for (i = 0; i < 2 * r; i++)
        {
          size_t j;
          printf ("B'[%d] =", (int)i);
          for (j = 0; j < 64; j++)
            {
              if (j && !(j % 16))
                printf ("\n       ");
              printf (" %02x", B[i * 64 + j]);
            }
          putchar ('\n');
        }
    }
#endif
}
