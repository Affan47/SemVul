bfd_elf_link_record_dynamic_symbol (struct bfd_link_info *info,
				    struct elf_link_hash_entry *h)
{
  if (h->dynindx == -1)
    {
      struct elf_strtab_hash *dynstr;
      char *p;
      const char *name;
      bfd_size_type indx;


      switch (ELF_ST_VISIBILITY (h->other))
	{
	case STV_INTERNAL:
	case STV_HIDDEN:
	  if (h->root.type != bfd_link_hash_undefined
	      && h->root.type != bfd_link_hash_undefweak)
	    {
	      h->forced_local = 1;
	      if (!elf_hash_table (info)->is_relocatable_executable)
		return TRUE;
	    }

	default:
	  break;
	}

      h->dynindx = elf_hash_table (info)->dynsymcount;
      ++elf_hash_table (info)->dynsymcount;

      dynstr = elf_hash_table (info)->dynstr;
      if (dynstr == NULL)
	{

	  elf_hash_table (info)->dynstr = dynstr = _bfd_elf_strtab_init ();
	  if (dynstr == NULL)
	    return FALSE;
	}


      name = h->root.root.string;
      p = strchr (name, ELF_VER_CHR);
      if (p != NULL)


	*p = 0;

      indx = _bfd_elf_strtab_add (dynstr, name, p != NULL);

      if (p != NULL)
	*p = ELF_VER_CHR;

      if (indx == (bfd_size_type) -1)
	return FALSE;
      h->dynstr_index = indx;
    }

  return TRUE;
}
