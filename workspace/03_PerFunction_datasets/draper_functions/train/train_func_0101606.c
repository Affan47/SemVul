rleIt(char *buf, char *bufto, int len)
{
    char *p, *q, *cfoll, *clead;
    char       *begp;
    int         i;

    p = buf;
    cfoll = bufto;
    clead = cfoll + 1;

    begp = p;
    while (len > 0)
      {

          q = p + 1;
          i = len - 1;
          while (*p == *q && i + 120 > len && i)
            {
                q++;
                i--;
            }

          if (q > p + 2)
            {
                if (p > begp)
                  {
                      *cfoll = (char) (p - begp);
                      cfoll = clead;
                  }
                *cfoll++ = (char) (128 | (q - p));
                *cfoll++ = *p;
                len -= (int) (q - p);
                p = q;
                clead = cfoll + 1;
                begp = p;
            }
          else
            {
                *clead++ = *p++;
                len--;
                if (p > begp + 120)
                  {
                      *cfoll = (char) (p - begp);
                      cfoll = clead++;
                      begp = p;
                  }
            }

      }


    if (p > begp)
        *cfoll = (char) (p - begp);
    else
        clead--;

    return ((int) (clead - bufto));
}
