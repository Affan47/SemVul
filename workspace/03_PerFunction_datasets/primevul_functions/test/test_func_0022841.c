ha_rows st_select_lex::get_limit()
{
  ulonglong val= HA_POS_ERROR;

  if (select_limit)
  {


    bool fix_fields_successful= true;
    if (!select_limit->fixed)
    {
      fix_fields_successful= !select_limit->fix_fields(master_unit()->thd,
                                                       NULL);

      DBUG_ASSERT(fix_fields_successful);
    }
    val= fix_fields_successful ? select_limit->val_uint() : HA_POS_ERROR;
  }

  return (ha_rows)val;
}
