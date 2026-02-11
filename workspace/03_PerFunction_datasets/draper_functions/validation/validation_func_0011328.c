Collect_Singleton(WamWord *adr)
{
  long *p;

  for (p = glob_dico_var; p < singl_var_ptr; p++)
    if ((*p & ~1) == (long) adr)
      {
	if ((*p & 1) == 0)
	  {
	    *p |= 1;
	    nb_singl_var--;
	  }
	return;
      }

  if (singl_var_ptr - glob_dico_var >= MAX_VAR_IN_TERM)
    Pl_Err_Representation(representation_too_many_variables);

  *singl_var_ptr++ = (long) adr;
  nb_singl_var++;
}
