union_defs (df_ref use, struct web_entry *def_entry,
	    unsigned int *used, struct web_entry *use_entry,
 	    bool (*fun) (struct web_entry *, struct web_entry *))
{
  struct df_insn_info *insn_info = DF_REF_INSN_INFO (use);
  struct df_link *link = DF_REF_CHAIN (use);
  df_ref *eq_use_link;
  df_ref *def_link;
  rtx set;

  if (insn_info)
    {
      rtx insn = insn_info->insn;
      eq_use_link = DF_INSN_INFO_EQ_USES (insn_info);
      def_link = DF_INSN_INFO_DEFS (insn_info);
      set = single_set (insn);
    }
  else
    {

      eq_use_link = NULL;
      def_link = NULL;
      set = NULL;
    }


  if (eq_use_link)
    while (*eq_use_link)
      {
	if (use != *eq_use_link
	    && DF_REF_REAL_REG (use) == DF_REF_REAL_REG (*eq_use_link))
	  (*fun) (use_entry + DF_REF_ID (use),
		  use_entry + DF_REF_ID (*eq_use_link));
	eq_use_link++;
    }


  if (set
      && SET_SRC (set) == DF_REF_REG (use)
      && SET_SRC (set) == SET_DEST (set))
    {
      if (def_link)
	while (*def_link)
	  {
	    if (DF_REF_REAL_REG (use) == DF_REF_REAL_REG (*def_link))
	      (*fun) (use_entry + DF_REF_ID (use),
		      def_entry + DF_REF_ID (*def_link));
	    def_link++;
	  }
    }


  if (!link)
    {
      int regno = REGNO (DF_REF_REAL_REG (use));
      if (used[regno])
	(*fun) (use_entry + DF_REF_ID (use), use_entry + used[regno] - 2);
      else
	used[regno] = DF_REF_ID (use) + 2;
    }

  while (link)
    {
      (*fun) (use_entry + DF_REF_ID (use),
	      def_entry + DF_REF_ID (link->ref));
      link = link->next;
    }


  if (DF_REF_FLAGS (use) & DF_REF_READ_WRITE)
    {
      df_ref *link;

      if (insn_info)
	link = DF_INSN_INFO_DEFS (insn_info);
      else
	link = NULL;

      if (link)
	while (*link)
	  {
	    if (DF_REF_REAL_REG (*link) == DF_REF_REAL_REG (use))
	      (*fun) (use_entry + DF_REF_ID (use),
		      def_entry + DF_REF_ID (*link));
	    link++;
	  }
    }
}
