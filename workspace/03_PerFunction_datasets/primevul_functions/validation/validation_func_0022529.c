join_read_always_key_or_null(JOIN_TAB *tab)
{
  int res;


  *tab->ref.null_ref_key= 0;
  if ((res= join_read_always_key(tab)) >= 0)
    return res;


  *tab->ref.null_ref_key= 1;
  return safe_index_read(tab);
}
