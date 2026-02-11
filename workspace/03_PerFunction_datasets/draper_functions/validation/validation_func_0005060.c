calc_bubble_area(struct state *st, int r)

{
#ifdef DEBUG
  printf("%d %g\n", r,
	 10.0 * PI * (double)r * (double)r * (double)r);
#endif
  if (st->threed)
    return (long)(10.0 * PI * (double)r * (double)r * (double)r);
  else
    return (long)(10.0 * PI * (double)r * (double)r);
}
