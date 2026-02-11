read_indirect_string (unit, buf, bytes_read_ptr)
     struct comp_unit* unit;
     char *buf;
     unsigned int *bytes_read_ptr;
{
  bfd_vma offset;
  struct dwarf2_debug *stash = unit->stash;

  if (unit->offset_size == 4)
    offset = read_4_bytes (unit->abfd, buf);
  else
    offset = read_8_bytes (unit->abfd, buf);
  *bytes_read_ptr = unit->offset_size;

  if (! stash->dwarf_str_buffer)
    {
      asection *msec;
      bfd *abfd = unit->abfd;

      msec = bfd_get_section_by_name (abfd, ".debug_str");
      if (! msec)
	{
	  (*_bfd_error_handler)
	    (_("Dwarf Error: Can't find .debug_str section."));
	  bfd_set_error (bfd_error_bad_value);
	  return NULL;
	}

      stash->dwarf_str_size = msec->_raw_size;
      stash->dwarf_str_buffer = (char*) bfd_alloc (abfd, msec->_raw_size);
      if (! stash->dwarf_abbrev_buffer)
	return NULL;

      if (! bfd_get_section_contents (abfd, msec, stash->dwarf_str_buffer,
				      (bfd_vma) 0, msec->_raw_size))
	return NULL;
    }

  if (offset >= stash->dwarf_str_size)
    {
      (*_bfd_error_handler) (_("Dwarf Error: DW_FORM_strp offset (%lu) greater than or equal to .debug_str size (%lu)."),
			     (unsigned long) offset, stash->dwarf_str_size);
      bfd_set_error (bfd_error_bad_value);
      return NULL;
    }

  buf = stash->dwarf_str_buffer + offset;
  if (*buf == '\0')
    return NULL;
  return buf;
}
