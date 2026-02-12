void Item_maxmin_subselect::cleanup()
{
  DBUG_ENTER("Item_maxmin_subselect::cleanup");
  Item_singlerow_subselect::cleanup();


  was_values= TRUE;
  DBUG_VOID_RETURN;
}
