Scan_Dynamic_Pred(int owner_func, int owner_arity,
		  DynPInf *dyn, WamWord first_arg_word,
		  ScanFct alt_fct, int alt_fct_type,
		  int alt_info_size, WamWord *alt_info)
{
  int index_no;
  long key;
  char **p_ind_htbl;
  DSwtInf *swt;
  DynScan scan;
  DynCInf *clause;
  WamWord *adr;
  int i;
  CodePtr scan_alt;

  if (owner_func < 0)
    owner_func = Get_Current_Bip(&owner_arity);

  index_no = (dyn->arity) ? Index_From_First_Arg(first_arg_word, &key)
    : NO_INDEX;

  scan.alt_fct = alt_fct;
  scan.alt_size_info = alt_info_size;
  scan.owner_func = owner_func;
  scan.owner_arity = owner_arity;
  scan.dyn = dyn;
  scan.stop_cl_no = dyn->count_z;
  scan.erase_stamp = erase_stamp++;

  switch (index_no)
    {
    case NO_INDEX:
    case VAR_INDEX:
      scan.xxx_is_seq_chain = TRUE;
      scan.xxx_ind_chain = dyn->seq_chain.first;
      p_ind_htbl = NULL;
      break;

    case LST_INDEX:
      scan.xxx_is_seq_chain = FALSE;
      scan.xxx_ind_chain = dyn->lst_ind_chain.first;
      p_ind_htbl = NULL;
      break;

    case ATM_INDEX:
      p_ind_htbl = &(dyn->atm_htbl);
      break;

    case INT_INDEX:
      p_ind_htbl = &(dyn->int_htbl);
      break;

    case STC_INDEX:
      p_ind_htbl = &(dyn->stc_htbl);
      break;

    }

  if (p_ind_htbl)
    {
      scan.xxx_is_seq_chain = FALSE;
      if (*p_ind_htbl &&
	  (swt = (DSwtInf *) Hash_Find(*p_ind_htbl, key)) != NULL)
	scan.xxx_ind_chain = swt->ind_chain.first;
      else
	scan.xxx_ind_chain = NULL;
    }

  if (scan.xxx_is_seq_chain)
    scan.var_ind_chain = NULL;
  else
    scan.var_ind_chain = dyn->var_ind_chain.first;

  clause = Scan_Dynamic_Pred_Next(&scan);
  if (clause == NULL)
    return NULL;

  if (Scan_Dynamic_Pred_Next(&scan) != NULL)
    {
      i = (sizeof(DynScan) + sizeof(WamWord) - 1) / sizeof(WamWord) +
	alt_info_size;

      if (alt_fct_type == DYN_ALT_FCT_FOR_TEST)
	scan_alt = (CodePtr) Prolog_Predicate(SCAN_DYN_TEST_ALT, 0);
      else
	scan_alt = (CodePtr) Prolog_Predicate(SCAN_DYN_JUMP_ALT, 0);

      Create_Choice_Point(scan_alt, i);
      adr = &AB(B, i) + 1;

      i = alt_info_size;
      while (i--)
	*adr++ = *alt_info++;

      *(DynScan *) adr = scan;
    }

  return clause;
}
