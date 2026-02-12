void Item_param::set_null()
{
  DBUG_ENTER("Item_param::set_null");

  null_value= 1;


  max_length= 0;
  decimals= 0;
  state= NULL_VALUE;
  item_type= Item::NULL_ITEM;
  DBUG_VOID_RETURN;
}
