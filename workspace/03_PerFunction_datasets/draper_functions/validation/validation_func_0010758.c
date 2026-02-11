lam_arr_insert(lam_array_t *la, void *element, int before)
{
  int i, size;


  if (before >= la->la_num_allocated) {
    size = la->la_num_allocated;
    while (size < before + 1)
      size += alloc_block;
    if (expand_array(la, size - (la->la_num_allocated)) == LAMERROR)
      return LAMERROR;
  }


  if (la->la_num_used == la->la_num_allocated ||
      before >= la->la_num_allocated)
    if (expand_array(la, alloc_block) == LAMERROR)
      return LAMERROR;


  for (i = la->la_num_used; i >= before; --i)
    memcpy(la->la_array + ((i + 1) * la->la_element_size),
	   la->la_array + (i * la->la_element_size),
	   la->la_element_size);
  ++la->la_num_used;


  memcpy(la->la_array + (before * la->la_element_size), element,
	 la->la_element_size);
  return 0;
}
