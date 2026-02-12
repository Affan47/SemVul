string_catn(gstring * g, const uschar *s, int count)
{
int p;

if (!g)
  {
  unsigned inc = count < 4096 ? 127 : 1023;
  unsigned size = ((count + inc) &  ~inc) + 1;
  g = string_get(size);
  }

p = g->ptr;
if (p + count >= g->size)
  gstring_grow(g, p, count);


memcpy(g->s + p, s, count);
g->ptr = p + count;
return g;
}
