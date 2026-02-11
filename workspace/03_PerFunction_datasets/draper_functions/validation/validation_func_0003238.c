is_empty_list (const struct format_arg_list *list)
{
  return (list->initial.count == 0 && list->repeated.count == 0);
}
