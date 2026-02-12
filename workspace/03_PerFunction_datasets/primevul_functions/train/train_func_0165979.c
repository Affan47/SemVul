int huft_free(t)
struct huft *t;


{
  register struct huft *p, *q;


  p = t;
  while (p != (struct huft *)NULL)
  {
    q = (--p)->v.t;
    free((char*)p);
    p = q;
  }
  return 0;
}
