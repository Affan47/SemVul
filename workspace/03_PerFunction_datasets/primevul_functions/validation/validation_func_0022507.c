JOIN::add_sorting_to_table(JOIN_TAB *tab, ORDER *order)
{
  tab->filesort=
    new (thd->mem_root) Filesort(order, HA_POS_ERROR, tab->keep_current_rowid,
                                 tab->select);
  if (!tab->filesort)
    return true;


  if (tab->select)
  {
    tab->select= NULL;
    tab->set_select_cond(NULL, __LINE__);
  }
  tab->read_first_record= join_init_read_record;
  return false;
}
