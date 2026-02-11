debugger_expression_evaluate( debugger_expression *exp )
{
  switch( exp->type ) {

  case DEBUGGER_EXPRESSION_TYPE_INTEGER:
    return exp->types.integer;

  case DEBUGGER_EXPRESSION_TYPE_REGISTER:
    return debugger_register_get( exp->types.reg );

  case DEBUGGER_EXPRESSION_TYPE_UNARYOP:
    return evaluate_unaryop( &( exp->types.unaryop ) );

  case DEBUGGER_EXPRESSION_TYPE_BINARYOP:
    return evaluate_binaryop( &( exp->types.binaryop ) );

  case DEBUGGER_EXPRESSION_TYPE_VARIABLE:
    return debugger_variable_get( exp->types.variable );

  }

  ui_error( UI_ERROR_ERROR, "unknown expression type %d", exp->type );
  fuse_abort();
}
