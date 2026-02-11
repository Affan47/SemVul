df_bb_reg_def_chain_create (df, bb)
     struct df *df;
     basic_block bb;
{
  rtx insn;


  for (insn = bb->end; insn && insn != PREV_INSN (bb->head);
       insn = PREV_INSN (insn))
    {
      struct df_link *link;
      unsigned int uid = INSN_UID (insn);

      if (! INSN_P (insn))
	continue;

      for (link = df->insns[uid].defs; link; link = link->next)
	{
	  struct ref *def = link->ref;
	  unsigned int dregno = DF_REF_REGNO (def);


          if (DF_REF_ID (def) < df->def_id_save)
            continue;

	  df->regs[dregno].defs
	    = df_link_create (def, df->regs[dregno].defs);
	}
    }
}
