dsvec_streq(Dsvec *dsv1, Dsvec *dsv2)
{
  unsigned int i;

  if (dsvec_len(dsv1) != dsvec_len(dsv2))
	return(0);

  for (i = 0; i < dsvec_len(dsv1); i++) {
	char *p, *q;

	p = (char *) dsvec_ptr_index(dsv1, i);
	q = (char *) dsvec_ptr_index(dsv2, i);
	if (!streq(p, q))
	  return(0);
  }

  return(1);
}
