bool value_depends_on_sql_mode_const_item()
  {


    DBUG_ASSERT(!is_expensive());


    return basic_const_item();
  }
