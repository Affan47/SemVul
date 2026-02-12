bool is_valid_limit_clause_variable_with_error() const
  {


    if (type_handler()->is_limit_clause_valid_type())
      return true;
    my_error(ER_WRONG_SPVAR_TYPE_IN_LIMIT, MYF(0));
    return false;
  }
