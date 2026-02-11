expression_op_func__exponent(
               expression*     expr,
   thread*         thr,
   const sim_time* time
) { PROFILE(EXPRESSION_OP_FUNC__EXPONENT);

  bool retval;


  if( !vector_is_unknown( expr->left->value ) && !vector_is_unknown( expr->right->value ) ) {

    int   intval1;
    int   intval2;
    ulong vall = 1;
    ulong valh = 0;
    int   i;

    intval1 = vector_to_int( expr->left->value );
    intval2 = vector_to_int( expr->right->value );

    for( i=0; i<intval2; i++ ) {
      vall *= intval1;
    }


    retval = vector_set_coverage_and_assign_ulong( expr->value, &vall, &valh, 0, 31 );


  } else {

    retval = vector_set_to_x( expr->value );

  }


  expression_set_tf_preclear( expr, retval );
  vector_set_unary_evals( expr->value );

  PROFILE_END;

  return( retval );

}
