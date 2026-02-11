ap_lincons0_array_add_dimensions(ap_lincons0_array_t* array,
						     ap_dimchange_t* dimchange)
{
  size_t i;
  ap_lincons0_array_t narray;

  narray = ap_lincons0_array_make(array->size);
  for(i=0; i<array->size; i++){
    narray.p[i] =  ap_lincons0_add_dimensions(&array->p[i],dimchange);
  }
  return narray;
}
