xsh_dispersol_list_load( cpl_frame *frame,
  xsh_instrument *instrument)
{
  xsh_dispersol_list *result = NULL;
  const char* tablename = NULL;
  cpl_table* table = NULL;
  int rows;

  int degx, degy;
  char coefname[20];
  int i;


  XSH_ASSURE_NOT_ILLEGAL( frame);


  check( tablename = cpl_frame_get_filename(frame));

  XSH_TABLE_LOAD( table, tablename);
  check( rows = cpl_table_get_nrow( table));


  check( xsh_get_table_value( table, XSH_DISPERSOL_TABLE_COLNAME_DEGX,
    CPL_TYPE_INT, 0, &degx));

  check( xsh_get_table_value( table, XSH_DISPERSOL_TABLE_COLNAME_DEGY,
    CPL_TYPE_INT, 0, &degy));

  check( result = xsh_dispersol_list_new( rows/2, degx, degy, instrument));

  for(i=0; i< rows/2; i++){
    cpl_polynomial *lambda_poly = NULL;
    cpl_polynomial *slit_poly = NULL;
    cpl_size pows[2];
    int k,l, absorder = 0;
    int j = 2*i;

    check( xsh_get_table_value( table, XSH_DISPERSOL_TABLE_COLNAME_ORDER,
      CPL_TYPE_INT, j, &absorder));
    check( lambda_poly = cpl_polynomial_new( 2));
    check( slit_poly = cpl_polynomial_new( 2));
    for( k=0; k<= degx; k++){
      for( l=0;  l<= degy; l++){
        double coef_lambda = 0.0, coef_slit = 0.0;
        sprintf(coefname,"C%d%d",k,l);
        check( xsh_get_table_value( table, coefname,CPL_TYPE_DOUBLE, j,
          &coef_lambda));
        check( xsh_get_table_value( table, coefname,CPL_TYPE_DOUBLE, j+1,
          &coef_slit));
        pows[0] =k;
        pows[1] = l;
        check( cpl_polynomial_set_coeff( lambda_poly, pows, coef_lambda));
        check( cpl_polynomial_set_coeff( slit_poly, pows, coef_slit));
      }
    }
    check( xsh_dispersol_list_add( result, i, absorder, lambda_poly, slit_poly));
  }

  cleanup:
    xsh_free_table( &table);
    if ( cpl_error_get_code() != CPL_ERROR_NONE) {
      xsh_dispersol_list_free( &result);
    }
    return result;
}
