virtual bool fix_fields(THD *, Item **)
  {


    DBUG_ASSERT(is_fixed());
    DBUG_ASSERT(basic_const_item());
    return false;
  }
