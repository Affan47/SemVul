bool Item_sp_variable::fix_fields(THD *thd, Item **)
{
  Item *it;

  m_thd= thd;
  it= this_item();

  DBUG_ASSERT(it->fixed);

  max_length= it->max_length;
  decimals= it->decimals;
  unsigned_flag= it->unsigned_flag;
  fixed= 1;
  collation.set(it->collation.collation, it->collation.derivation);

  return FALSE;
}
