cbf_alloc (void **new_block, size_t *new_nelem,
               size_t elsize, size_t nelem)
{


  if (!new_block)

    return CBF_ARGUMENT;


  *new_block = NULL;

  if (new_nelem)

    *new_nelem = 0;


  return cbf_realloc (new_block, new_nelem, elsize, nelem);
}
