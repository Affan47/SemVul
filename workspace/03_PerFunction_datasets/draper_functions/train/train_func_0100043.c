super_fgets_w(char **b, size_t *blen, Image *file)
{
  size_t
    len;

  int
    c;

  unsigned char
    *p,
    *q;

  len=*blen;
  p=(unsigned char *) (*b);
  for (q=p; ; q++)
  {
    c=ReadBlobLSBShort(file);
    if (c == ((unsigned short) ~0U) || c == '\n')
      break;
   if (EOFBlob(file))
      break;
   if ((q-p+1) >= (int) len)
      {
        int
          tlen;

        tlen=q-p;
        len<<=1;
        MagickReallocMemory(unsigned char *,p,(len+2));
        *b=(char *) p;
        if (p == (unsigned char *) NULL)
          break;
        q=p+tlen;
      }
    *q=(unsigned char) c;
  }
  *blen=0;
  if ((*b) != (char *) NULL)
    {
      int
        tlen;

      tlen=q-p;
      if (tlen == 0)
        return (char *) NULL;
      p[tlen] = '\0';
      *blen=++tlen;
    }
  return (char *) p;
}
