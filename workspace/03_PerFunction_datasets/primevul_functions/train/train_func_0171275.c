bool Item_exists_subselect::fix_length_and_dec()
{
  DBUG_ENTER("Item_exists_subselect::fix_length_and_dec");
  init_length_and_dec();

  if (!unit->global_parameters()->select_limit ||
      (unit->global_parameters()->select_limit->basic_const_item() &&
       unit->global_parameters()->select_limit->val_int() > 1))
  {


    Item *item= new (thd->mem_root) Item_int(thd, (int32) 1);
    if (!item)
      DBUG_RETURN(TRUE);
    thd->change_item_tree(&unit->global_parameters()->select_limit,
                          item);
    unit->global_parameters()->explicit_limit= 1;
    DBUG_PRINT("info", ("Set limit to 1"));
  }
  DBUG_RETURN(FALSE);
}
