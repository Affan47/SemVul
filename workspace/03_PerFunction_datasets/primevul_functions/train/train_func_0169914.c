bool Item_trigger_field::set_value(THD *thd, sp_rcontext * , Item **it)
{
  Item *item= sp_prepare_func_item(thd, it);

  if (!item)
    return true;

  if (!fixed)
  {
    if (fix_fields(thd, NULL))
      return true;
  }


  bool copy_blobs_saved= field->table->copy_blobs;

  field->table->copy_blobs= true;

  int err_code= item->save_in_field(field, 0);

  field->table->copy_blobs= copy_blobs_saved;

  return err_code < 0;
}
