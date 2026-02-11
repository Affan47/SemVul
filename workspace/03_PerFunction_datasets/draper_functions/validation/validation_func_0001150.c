df_bb_regno_first_def_find (struct df *df, basic_block bb, unsigned int regno)
{
  struct df_link *link;


  for (link = df->regs[regno].defs; link; link = link->next)
    {
      struct ref *def = link->ref;

      if (DF_REF_BB (def) == bb)
	return def;
    }
  return 0;
}
