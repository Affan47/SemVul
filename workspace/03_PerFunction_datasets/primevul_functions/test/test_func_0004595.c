check_uvalue (const unsigned char * start,
	      dwarf_vma             uvalue,
	      const unsigned char * end)
{
  dwarf_vma max_uvalue = end - start;


  if (uvalue > max_uvalue)
    {
      warn (_("Corrupt attribute block length: %lx\n"), (long) uvalue);
      uvalue = max_uvalue;
    }

  return uvalue;
}
