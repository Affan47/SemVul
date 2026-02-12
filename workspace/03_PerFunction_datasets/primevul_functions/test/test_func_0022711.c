virtual bool handle_condition(THD *thd,
                                  uint sql_errno,
                                  const char* sqlstate,
                                  Sql_condition::enum_warning_level *level,
                                  const char* msg,
                                  Sql_condition ** cond_hdl)
  {
    if (sql_errno == ER_LOCK_DEADLOCK)
    {
      thd->mark_transaction_to_rollback(true);
    }


    return false;
  }
