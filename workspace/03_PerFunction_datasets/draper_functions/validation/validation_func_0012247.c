generic_add_output_symbol (bfd *output_bfd, size_t *psymalloc, asymbol *sym)
{
  if (bfd_get_symcount (output_bfd) >= *psymalloc)
    {
      asymbol **newsyms;
      bfd_size_type amt;

      if (*psymalloc == 0)
	*psymalloc = 124;
      else
	*psymalloc *= 2;
      amt = *psymalloc;
      amt *= sizeof (asymbol *);
      newsyms = (asymbol **) bfd_realloc (bfd_get_outsymbols (output_bfd), amt);
      if (newsyms == NULL)
	return FALSE;
      bfd_get_outsymbols (output_bfd) = newsyms;
    }

  bfd_get_outsymbols (output_bfd) [bfd_get_symcount (output_bfd)] = sym;
  if (sym != NULL)
    ++ bfd_get_symcount (output_bfd);

  return TRUE;
}
