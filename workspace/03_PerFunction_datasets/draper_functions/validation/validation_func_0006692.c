xsh_wavesol_duplicate( xsh_wavesol * org )
{
  xsh_wavesol * res = NULL ;

  XSH_MALLOC( res, xsh_wavesol, 1 ) ;
  res->bin_x = org->bin_x ;
  res->bin_y = org->bin_y ;
  res->deg_slit = org->deg_slit ;
  res->deg_order = org->deg_order ;
  res->deg_lambda = org->deg_lambda ;
  res->min_lambda = org->min_lambda ;
  res->max_lambda = org->max_lambda ;
  res->min_order = org->min_order ;
  res->max_order = org->max_order ;
  res->min_slit = org->min_slit ;
  res->max_slit = org->max_slit ;
  res->min_x = org->min_x ;
  res->max_x = org->max_x ;
  res->min_y = org->min_y ;
  res->max_y = org->max_y ;
  res->nbcoefs = org->nbcoefs ;
  res->polx = cpl_polynomial_duplicate( org->polx ) ;
  res->poly = cpl_polynomial_duplicate( org->poly ) ;
  res->dim = cpl_vector_duplicate( org->dim ) ;
  res->header = cpl_propertylist_duplicate( org->header ) ;

 cleanup:
  return res ;
}
