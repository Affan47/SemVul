int huft_build(b, n, s, d, e, t, m)
unsigned *b;
unsigned n;
unsigned s;
ush *d;
ush *e;
struct huft **t;
int *m;


{
  unsigned a;
  unsigned c[BMAX+1];
  unsigned f;
  int g;
  int h;
  register unsigned i;
  register unsigned j;
  register int k;
  int l;
  register unsigned *p;
  register struct huft *q;
  struct huft r;
  struct huft *u[BMAX];
  unsigned v[N_MAX];
  register int w;
  unsigned x[BMAX+1];
  unsigned *xp;
  int y;
  unsigned z;


  memzero(c, sizeof(c));
  p = b;  i = n;
  do {
    Tracecv(*p, (stderr, (n-i >= ' ' && n-i <= '~' ? "%c %d\n" : "0x%x %d\n"),
	    n-i, *p));
    c[*p]++;
    p++;
  } while (--i);
  if (c[0] == n)
  {
    q = (struct huft *) malloc (2 * sizeof *q);
    if (!q)
      return 3;
    hufts += 2;
    q[0].v.t = (struct huft *) NULL;
    q[1].e = 99;
    q[1].b = 1;
    *t = q + 1;
    *m = 1;
    return 0;
  }


  l = *m;
  for (j = 1; j <= BMAX; j++)
    if (c[j])
      break;
  k = j;
  if ((unsigned)l < j)
    l = j;
  for (i = BMAX; i; i--)
    if (c[i])
      break;
  g = i;
  if ((unsigned)l > i)
    l = i;
  *m = l;


  for (y = 1 << j; j < i; j++, y <<= 1)
    if ((y -= c[j]) < 0)
      return 2;
  if ((y -= c[i]) < 0)
    return 2;
  c[i] += y;


  x[1] = j = 0;
  p = c + 1;  xp = x + 2;
  while (--i) {
    *xp++ = (j += *p++);
  }


  p = b;  i = 0;
  do {
    if ((j = *p++) != 0)
      v[x[j]++] = i;
  } while (++i < n);
  n = x[g];


  x[0] = i = 0;
  p = v;
  h = -1;
  w = -l;
  u[0] = (struct huft *)NULL;
  q = (struct huft *)NULL;
  z = 0;


  for (; k <= g; k++)
  {
    a = c[k];
    while (a--)
    {


      while (k > w + l)
      {
        h++;
        w += l;


        z = (z = g - w) > (unsigned)l ? l : z;
        if ((f = 1 << (j = k - w)) > a + 1)
        {
          f -= a + 1;
          xp = c + k;
	  if (j < z)
	    while (++j < z)
	    {
	      if ((f <<= 1) <= *++xp)
		break;
	      f -= *xp;
	    }
        }
        z = 1 << j;


        if ((q = (struct huft *)malloc((z + 1)*sizeof(struct huft))) ==
            (struct huft *)NULL)
        {
          if (h)
            huft_free(u[0]);
          return 3;
        }
        hufts += z + 1;
        *t = q + 1;
        *(t = &(q->v.t)) = (struct huft *)NULL;
        u[h] = ++q;


        if (h)
        {
          x[h] = i;
          r.b = (uch)l;
          r.e = (uch)(16 + j);
          r.v.t = q;
          j = i >> (w - l);
          u[h-1][j] = r;
        }
      }


      r.b = (uch)(k - w);
      if (p >= v + n)
        r.e = 99;
      else if (*p < s)
      {
        r.e = (uch)(*p < 256 ? 16 : 15);
        r.v.n = (ush)(*p);
	p++;
      }
      else
      {
        r.e = (uch)e[*p - s];
        r.v.n = d[*p++ - s];
      }


      f = 1 << (k - w);
      for (j = i >> w; j < z; j += f)
        q[j] = r;


      for (j = 1 << (k - 1); i & j; j >>= 1)
        i ^= j;
      i ^= j;


      while ((i & ((1 << w) - 1)) != x[h])
      {
        h--;
        w -= l;
      }
    }
  }


  return y != 0 && g != 1;
}
