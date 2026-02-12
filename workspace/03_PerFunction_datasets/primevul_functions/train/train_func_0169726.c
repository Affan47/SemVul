void Item_ident::cleanup()
{
  DBUG_ENTER("Item_ident::cleanup");
  bool was_fixed= fixed;
  Item::cleanup();
  db_name= orig_db_name;
  table_name= orig_table_name;
  field_name= orig_field_name;

  if (was_fixed)
  {


    can_be_depended= test(depended_from);
  }
  DBUG_VOID_RETURN;
}
