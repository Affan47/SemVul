SR_Current_Descriptor_Alt_0(void)
{
  WamWord desc_word;
  int desc;

  Update_Choice_Point((CodePtr) Prolog_Predicate(SR_CURRENT_DESC_ALT, 0), 0);

  desc_word = AB(B, 0);
  desc = AB(B, 1);

  for (; desc <= sr_last_used; desc++)
    if (sr_tbl[desc].in_use)
      break;

  if (desc >= sr_last_used)
    {
      Delete_Last_Choice_Point();
      if (desc > sr_last_used)
	return FALSE;
    }
  else
    {
#if 0
      AB(B, 0) = desc_word;
#endif
      AB(B, 1) = desc + 1;
    }

  return Get_Integer(desc, desc_word);
}
