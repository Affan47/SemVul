fluid_list_nth(fluid_list_t *list, int n)
{
  while ((n-- > 0) && list) {
    list = list->next;
  }

  return list;
}
