coff_canonicalize_symtab (bfd *abfd, asymbol **alocation)
{
  unsigned int counter;
  coff_symbol_type *symbase;
  coff_symbol_type **location = (coff_symbol_type **) alocation;

  if (!bfd_coff_slurp_symbol_table (abfd))
    return -1;

  symbase = obj_symbols (abfd);
  counter = bfd_get_symcount (abfd);
  while (counter-- > 0)
    *location++ = symbase++;

  *location = NULL;

  return bfd_get_symcount (abfd);
}
