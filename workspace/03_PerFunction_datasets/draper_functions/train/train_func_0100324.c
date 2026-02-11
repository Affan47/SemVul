sumnsteps(node *p, node *left, node *rt, long a, long b)
{


  long i;
  unsigned char ns, rs, ls;

  if (!left) {
    memcpy(p->numsteps, rt->numsteps, endsite*sizeof(long));
    memcpy(p->discbase, rt->discbase, endsite*sizeof(unsigned char));
  } else if (!rt) {
    memcpy(p->numsteps, left->numsteps, endsite*sizeof(long));
    memcpy(p->discbase, left->discbase, endsite*sizeof(unsigned char));
  } else
    for (i = a; i < b; i++) {
      ls = left->discbase[i];
      rs = rt->discbase[i];
      ns = ls & rs;
      p->numsteps[i] = left->numsteps[i] + rt->numsteps[i];
      if (ns == 0) {
        ns = ls | rs;
        p->numsteps[i] += weight[i];
      }
      p->discbase[i] = ns;
    }
}
