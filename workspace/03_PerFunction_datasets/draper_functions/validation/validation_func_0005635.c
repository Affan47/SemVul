c_safe_from_p (target, exp)
     rtx target;
     tree exp;
{


  if (TREE_CODE (exp) == DECL_STMT)
    {
      tree decl = DECL_STMT_DECL (exp);

      if (TREE_CODE (decl) == VAR_DECL
	  && DECL_INITIAL (decl)
	  && !safe_from_p (target, DECL_INITIAL (decl), 0))
	return 0;
    }


  if (statement_code_p (TREE_CODE (exp)) && TREE_CHAIN (exp))
    return safe_from_p (target, TREE_CHAIN (exp), 0);


  return 1;
}
