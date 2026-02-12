longlong Item_in_optimizer::val_int()
{
  bool tmp;
  DBUG_ASSERT(fixed == 1);
  cache->store(args[0]);
  cache->cache_value();
  DBUG_ENTER(" Item_in_optimizer::val_int");

  if (invisible_mode())
  {
    longlong res= args[1]->val_int();
    null_value= args[1]->null_value;
    DBUG_PRINT("info", ("pass trough"));
    DBUG_RETURN(res);
  }

  if (cache->null_value_inside)
  {
     DBUG_PRINT("info", ("Left NULL..."));


    if (((Item_in_subselect*)args[1])->is_top_level_item())
    {


      null_value= 1;
    }
    else
    {


      Item_in_subselect *item_subs=(Item_in_subselect*)args[1];
      bool all_left_cols_null= true;
      const uint ncols= cache->cols();


      for (uint i= 0; i < ncols; i++)
      {
        if (cache->element_index(i)->null_value)
          item_subs->set_cond_guard_var(i, FALSE);
        else
          all_left_cols_null= false;
      }

      if (!item_subs->is_correlated &&
          all_left_cols_null && result_for_null_param != UNKNOWN)
      {


        null_value= result_for_null_param;
      }
      else
      {

        (void) item_subs->val_bool_result();
        if (item_subs->engine->no_rows())
          null_value= item_subs->null_value;
        else
          null_value= TRUE;
        if (all_left_cols_null)
          result_for_null_param= null_value;
      }


      for (uint i= 0; i < ncols; i++)
        item_subs->set_cond_guard_var(i, TRUE);
    }
    DBUG_RETURN(0);
  }
  tmp= args[1]->val_bool_result();
  null_value= args[1]->null_value;
  DBUG_RETURN(tmp);
}
