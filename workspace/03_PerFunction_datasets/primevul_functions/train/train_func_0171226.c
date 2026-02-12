subselect_single_select_engine::change_result(Item_subselect *si,
                                              select_result_interceptor *res,
                                              bool temp)
{
  DBUG_ENTER("subselect_single_select_engine::change_result");
  item= si;
  if (temp)
  {


    thd->change_item_tree((Item**) &result, (Item*)res);
  }
  else
    result= res;


  DBUG_RETURN(select_lex->join->change_result(res, NULL));
}
