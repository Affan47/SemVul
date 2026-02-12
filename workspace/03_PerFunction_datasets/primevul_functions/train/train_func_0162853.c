static void qp_decode_line (char *dest, char *src, size_t *l,
			    int last)
{
  char *d, *s;
  char c = 0;

  int kind = -1;
  int soft = 0;


  for (d = dest, s = src; *s;)
  {
    switch ((kind = qp_decode_triple (s, &c)))
    {
      case  0: *d++ = c; s += 3; break;
      case -1: *d++ = *s++;      break;
      case  1: soft = 1; s++;	 break;
    }
  }

  if (!soft && last == '\n')
  {


    if (kind == 0 && c == '\r')
      *(d-1) = '\n';
    else
      *d++ = '\n';
  }

  *d = '\0';
  *l = d - dest;
}
