df_rd_bb_local_compute_process_def (struct df_rd_bb_info *bb_info,
				    df_ref *def_rec,
				    int top_flag)
{
  while (*def_rec)
    {
      df_ref def = *def_rec;
      if (top_flag == (DF_REF_FLAGS (def) & DF_REF_AT_TOP))
	{
	  unsigned int regno = DF_REF_REGNO (def);
	  unsigned int begin = DF_DEFS_BEGIN (regno);
	  unsigned int n_defs = DF_DEFS_COUNT (regno);

	  if ((!(df->changeable_flags & DF_NO_HARD_REGS))
	      || (regno >= FIRST_PSEUDO_REGISTER))
	    {


	      if (!bitmap_bit_p (&seen_in_block, regno))
		{


		  if ((!bitmap_bit_p (&seen_in_insn, regno))


		      && (!(DF_REF_FLAGS (def) &
			    (DF_REF_PARTIAL | DF_REF_CONDITIONAL | DF_REF_MAY_CLOBBER))))
		    {
		      if (n_defs > DF_SPARSE_THRESHOLD)
			{
			  bitmap_set_bit (&bb_info->sparse_kill, regno);
			  bitmap_clear_range(&bb_info->gen, begin, n_defs);
			}
		      else
			{
			  bitmap_set_range (&bb_info->kill, begin, n_defs);
			  bitmap_clear_range (&bb_info->gen, begin, n_defs);
			}
		    }

		  bitmap_set_bit (&seen_in_insn, regno);


		  if (!(DF_REF_FLAGS (def)
			& (DF_REF_MUST_CLOBBER | DF_REF_MAY_CLOBBER)))
		    bitmap_set_bit (&bb_info->gen, DF_REF_ID (def));
		}
	    }
	}
      def_rec++;
    }
}
