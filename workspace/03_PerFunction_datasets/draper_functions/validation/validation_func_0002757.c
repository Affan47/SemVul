xsh_spectralformat_list_get_orders(
  xsh_spectralformat_list *list, float lambda)
{
  cpl_vector* result = NULL;
  int i;
  int size = 0;
  int order_tab[20];

  XSH_ASSURE_NOT_NULL(list);

  for( i = 0 ; i<list->size ; i++ ){
    float min=0.0, max=0.0;

    min = list->list[i].lambda_min_full;
    max = list->list[i].lambda_max_full;

    xsh_msg_dbg_high( "search lambda %f in [%f,%f]", lambda, min, max);

    if (lambda >= min && lambda <= max){
      order_tab[size] = list->list[i].absorder;
      size++;
    }
  }

  if (size > 0){
    check( result = cpl_vector_new( size));
    for( i=0; i< size; i++){
      check( cpl_vector_set( result, i, order_tab[i]));
    }
  }
  cleanup:
    if ( cpl_error_get_code() != CPL_ERROR_NONE){
      xsh_free_vector( &result);
    }
    return result;
}
