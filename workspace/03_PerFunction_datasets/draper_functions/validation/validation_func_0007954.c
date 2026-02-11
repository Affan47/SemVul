add_option(struct opt_odb_t *odb,
	   struct opt_opt_t *opt)
{
  struct opt_opt_t *elt, *prev;


  if (opt->name[0] != '-')
    panic("option `%s' must start with a `-'", opt->name);


  for (prev=NULL, elt=odb->options; elt != NULL; prev=elt, elt=elt->next)
    {

      if (elt->name[0] == opt->name[0] && !strcmp(elt->name, opt->name))
	panic("option `%s' is multiply defined", opt->name);
    }

  if (prev != NULL)
    prev->next = opt;
  else
    odb->options = opt;
  opt->next = NULL;
}
