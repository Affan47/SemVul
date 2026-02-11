check_dup(Dsvec *dsv, char *ref)
{
  int i;
  Service_ref *sr;

  for (i = 0; i < dsvec_len(dsv); i++) {
	sr = (Service_ref *) dsvec_ptr_index(dsv, i);
	if (streq(sr->ref, ref))
	  return(sr);
  }

  return(NULL);
}
