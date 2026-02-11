df_reorganize_refs_by_insn (struct df_ref_info *ref_info,
			    bool include_defs, bool include_uses,
			    bool include_eq_uses)
{
  basic_block bb;
  unsigned int offset = 0;

  ref_info->total_size = df_count_refs (include_defs, include_uses, include_eq_uses);
  df_check_and_grow_ref_info (ref_info, 1);
  if (df->blocks_to_analyze)
    {
      bitmap_iterator bi;
      unsigned int index;

      EXECUTE_IF_SET_IN_BITMAP (df->blocks_to_analyze, 0, index, bi)
	{
	  offset = df_reorganize_refs_by_insn_bb (BASIC_BLOCK (index), offset, ref_info,
						  include_defs, include_uses,
						  include_eq_uses);
	}

      ref_info->table_size = offset;
    }
  else
    {
      FOR_ALL_BB (bb)
	offset = df_reorganize_refs_by_insn_bb (bb, offset, ref_info,
						include_defs, include_uses,
						include_eq_uses);
      ref_info->table_size = offset;
    }
}
