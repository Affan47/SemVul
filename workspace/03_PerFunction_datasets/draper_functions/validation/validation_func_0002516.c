is_too_expensive (const char *pass)
{


  if (n_edges > 20000 + n_basic_blocks * 4)
    {
      warning (OPT_Wdisabled_optimization,
	       "%s: %d basic blocks and %d edges/basic block",
	       pass, n_basic_blocks, n_edges / n_basic_blocks);

      return true;
    }


  if ((n_basic_blocks
       * SBITMAP_SET_SIZE (max_reg_num ())
       * sizeof (SBITMAP_ELT_TYPE)) > MAX_GCSE_MEMORY)
    {
      warning (OPT_Wdisabled_optimization,
	       "%s: %d basic blocks and %d registers",
	       pass, n_basic_blocks, max_reg_num ());

      return true;
    }

  return false;
}
