dump_live_info (FILE *f, tree_live_info_p live, int flag)
{
  basic_block bb;
  unsigned i;
  var_map map = live->map;
  bitmap_iterator bi;

  if ((flag & LIVEDUMP_ENTRY) && live->livein)
    {
      FOR_EACH_BB (bb)
	{
	  fprintf (f, "\nLive on entry to BB%d : ", bb->index);
	  EXECUTE_IF_SET_IN_BITMAP (&live->livein[bb->index], 0, i, bi)
	    {
	      print_generic_expr (f, partition_to_var (map, i), TDF_SLIM);
	      fprintf (f, "  ");
	    }
	  fprintf (f, "\n");
	}
    }

  if ((flag & LIVEDUMP_EXIT) && live->liveout)
    {
      FOR_EACH_BB (bb)
	{
	  fprintf (f, "\nLive on exit from BB%d : ", bb->index);
	  EXECUTE_IF_SET_IN_BITMAP (&live->liveout[bb->index], 0, i, bi)
	    {
	      print_generic_expr (f, partition_to_var (map, i), TDF_SLIM);
	      fprintf (f, "  ");
	    }
	  fprintf (f, "\n");
	}
    }
}
