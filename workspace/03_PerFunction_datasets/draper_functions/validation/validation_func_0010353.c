finalize (void)
{

  if (flag_gen_aux_info)
    {
      fclose (aux_info_file);
      if (errorcount)
	unlink (aux_info_file_name);
    }


  if (asm_out_file)
    {
      if (ferror (asm_out_file) != 0)
	fatal_error ("error writing to %s: %m", asm_file_name);
      if (fclose (asm_out_file) != 0)
	fatal_error ("error closing %s: %m", asm_file_name);
    }


  if (graph_dump_format != no_graph)
    {
      int i;

      for (i = 0; i < (int) DFI_MAX; ++i)
	if (dump_file[i].initialized && dump_file[i].graph_dump_p)
	  {
	    char seq[16];
	    char *suffix;

	    sprintf (seq, DUMPFILE_FORMAT, i);
	    suffix = concat (seq, dump_file[i].extension, NULL);
	    finish_graph_dump_file (dump_base_name, suffix);
	    free (suffix);
	  }
    }

  if (mem_report)
    {
      ggc_print_statistics ();
      stringpool_statistics ();
      dump_tree_statistics ();
      dump_rtx_statistics ();
      dump_varray_statistics ();
      dump_alloc_pool_statistics ();
    }


  free_reg_info ();


  (*lang_hooks.finish) ();
}
