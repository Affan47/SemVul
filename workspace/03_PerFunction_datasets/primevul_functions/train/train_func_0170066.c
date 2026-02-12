void Item_field::cleanup()
{
  DBUG_ENTER("Item_field::cleanup");
  Item_ident::cleanup();
  depended_from= NULL;


  field= result_field= 0;
  item_equal= NULL;
  null_value= FALSE;
  DBUG_VOID_RETURN;
}
