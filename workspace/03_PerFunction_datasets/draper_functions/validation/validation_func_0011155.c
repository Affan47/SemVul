xsh_parameters_merge_ord_get( const char* recipe_id,
  cpl_parameterlist* list)
{
  xsh_merge_param *result = NULL;


  XSH_ASSURE_NOT_NULL( recipe_id);
  XSH_ASSURE_NOT_NULL( list);


  XSH_MALLOC( result, xsh_merge_param, 1);


  check( result->method = xsh_parameters_get_int( list, recipe_id,
    "mergeord-method"));

 cleanup:
  if(cpl_error_get_code() != CPL_ERROR_NONE){
    XSH_FREE( result);
  }
  return result;
}
