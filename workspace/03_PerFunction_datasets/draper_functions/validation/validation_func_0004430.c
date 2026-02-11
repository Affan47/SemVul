ivl_stmt_cond_expr(ivl_statement_t net)
{
      switch (net->type_) {
	  case IVL_ST_ASSIGN_NB:
	    return net->u_.assign_.count;

	  case IVL_ST_CONDIT:
	    return net->u_.condit_.cond_;

	  case IVL_ST_CASE:
	  case IVL_ST_CASER:
	  case IVL_ST_CASEX:
	  case IVL_ST_CASEZ:
	    return net->u_.case_.cond;

	  case IVL_ST_REPEAT:
	  case IVL_ST_WHILE:
	    return net->u_.while_.cond_;

	  default:
	    assert(0);
	    return 0;
      }
}
