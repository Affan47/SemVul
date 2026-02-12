frame_need_space (Frame_Chunk *fc, unsigned int reg)
{
  unsigned int prev = fc->ncols;

  if (reg < (unsigned int) fc->ncols)
    return 0;

  if (dwarf_regnames_count > 0
      && reg > dwarf_regnames_count)
    return -1;

  fc->ncols = reg + 1;


  if (fc->ncols == 0)
    return -1;


  if (fc->ncols > 1024 && dwarf_regnames_count == 0)
    {
      error (_("Unfeasibly large register number: %u\n"), reg);
      fc->ncols = 0;


      return -1;
    }

  fc->col_type = (short int *) xcrealloc (fc->col_type, fc->ncols,
					  sizeof (short int));
  fc->col_offset = (int *) xcrealloc (fc->col_offset, fc->ncols, sizeof (int));

  if (fc->col_type == NULL || fc->col_offset == NULL)
    {
      error (_("Out of memory allocating %u columns in dwarf frame arrays\n"),
	     fc->ncols);
      fc->ncols = 0;
      return -1;
    }

  while (prev < fc->ncols)
    {
      fc->col_type[prev] = DW_CFA_unreferenced;
      fc->col_offset[prev] = 0;
      prev++;
    }
  return 1;
}
