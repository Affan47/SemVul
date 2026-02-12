void Item_trigger_field::cleanup()
{
  want_privilege= original_privilege;


  Item::cleanup();
}
