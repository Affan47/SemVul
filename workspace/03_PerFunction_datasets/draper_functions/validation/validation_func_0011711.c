pop_int_list( int *list, int *n_list_ptr, int *value_ptr)
{
  int found_j_in = TRUE, i;

  *n_list_ptr = 0;
  for (i=0; list[i] != END_OF_INT_LIST; i++) {
    (*n_list_ptr)++;
    if (i == 0)
      *value_ptr = list[i];
  }
  if (*n_list_ptr > 0) {
    for (i=0; i<*n_list_ptr; i++)
      list[i] = list[i+1];
    (*n_list_ptr)--;
  }
  else
    found_j_in = FALSE;
  return (found_j_in);
}
