bool save_in_param(THD *thd, Item_param *param)
  {

    DBUG_ASSERT(arg == NULL);
    param->set_default();
    return false;
  }
