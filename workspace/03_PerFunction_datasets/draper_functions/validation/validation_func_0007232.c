regstat_bb_compute_calls_crossed (unsigned int bb_index, bitmap live)
{
  basic_block bb = BASIC_BLOCK (bb_index);
  rtx insn;
  df_ref *def_rec;
  df_ref *use_rec;

  bitmap_copy (live, df_get_live_out (bb));


  for (def_rec = df_get_artificial_defs (bb_index); *def_rec; def_rec++)
    {
      df_ref def = *def_rec;
      if ((DF_REF_FLAGS (def) & DF_REF_AT_TOP) == 0)
	bitmap_clear_bit (live, DF_REF_REGNO (def));
    }

  for (use_rec = df_get_artificial_uses (bb_index); *use_rec; use_rec++)
    {
      df_ref use = *use_rec;
      if ((DF_REF_FLAGS (use) & DF_REF_AT_TOP) == 0)
	bitmap_set_bit (live, DF_REF_REGNO (use));
    }

  FOR_BB_INSNS_REVERSE (bb, insn)
    {
      unsigned int uid = INSN_UID (insn);
      unsigned int regno;

      if (!INSN_P (insn))
	continue;


      if (CALL_P (insn))
	{
	  bitmap_iterator bi;
	  EXECUTE_IF_SET_IN_BITMAP (live, 0, regno, bi)
	    {
	      REG_N_CALLS_CROSSED (regno)++;
	      REG_FREQ_CALLS_CROSSED (regno) += REG_FREQ_FROM_BB (bb);
	    }
	}


      for (def_rec = DF_INSN_UID_DEFS (uid); *def_rec; def_rec++)
	{
	  df_ref def = *def_rec;
	  if ((!CALL_P (insn))
	      || (!(DF_REF_FLAGS (def) & (DF_REF_MUST_CLOBBER | DF_REF_MAY_CLOBBER))))
	    {

	      if (!(DF_REF_FLAGS (def) & (DF_REF_PARTIAL | DF_REF_CONDITIONAL)))
		bitmap_clear_bit (live, DF_REF_REGNO (def));
	    }
	}

      for (use_rec = DF_INSN_UID_USES (uid); *use_rec; use_rec++)
	{
	  df_ref use = *use_rec;
	  bitmap_set_bit (live, DF_REF_REGNO (use));
	}
    }
}
