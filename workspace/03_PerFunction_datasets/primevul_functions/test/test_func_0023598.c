bool save_in_param(THD *thd, Item_param *param)
  {

    DBUG_ASSERT(0);
    param->set_default();
    return false;
  }
