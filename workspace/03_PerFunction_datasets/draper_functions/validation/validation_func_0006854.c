oecount_eq (const void *p1, const void *p2)
{
  const oecount *c1 = &cvec[(size_t)p1 - 42];
  const oecount *c2 = &cvec[(size_t)p2 - 42];
  return (c1->oecode == c2->oecode
	  && c1->op == c2->op);
}
