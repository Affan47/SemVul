copy_funcs(Item **func_ptr, const THD *thd)
{
  Item *func;
  for (; (func = *func_ptr) ; func_ptr++)
  {
    if (func->type() == Item::FUNC_ITEM &&
        ((Item_func *) func)->with_window_func)
      continue;
    func->save_in_result_field(1);


    if (unlikely(thd->is_error()))
      return TRUE;
  }
  return FALSE;
}
