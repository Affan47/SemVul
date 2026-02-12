Item_in_subselect::single_value_transformer(JOIN *join)
{
  SELECT_LEX *select_lex= join->select_lex;
  DBUG_ENTER("Item_in_subselect::single_value_transformer");
  DBUG_ASSERT(thd == join->thd);


  if (select_lex->item_list.elements > 1)
  {
    my_error(ER_OPERAND_COLUMNS, MYF(0), 1);
    DBUG_RETURN(true);
  }

  Item* join_having= join->having ? join->having : join->tmp_having;
  if (!(join_having || select_lex->with_sum_func ||
        select_lex->group_list.elements) &&
      select_lex->table_list.elements == 0 && !join->conds &&
      !select_lex->master_unit()->is_union())
  {
    Item *where_item= (Item*) select_lex->item_list.head();


    where_item->walk(&Item::remove_dependence_processor, 0,
                     select_lex->outer_select());


    substitution= func->create(thd, left_expr, where_item);
    have_to_be_excluded= 1;
    if (thd->lex->describe)
    {
      char warn_buff[MYSQL_ERRMSG_SIZE];
      sprintf(warn_buff, ER_THD(thd, ER_SELECT_REDUCED),
              select_lex->select_number);
      push_warning(thd, Sql_condition::WARN_LEVEL_NOTE,
                   ER_SELECT_REDUCED, warn_buff);
    }
    DBUG_RETURN(false);
  }


  if (!substitution)
  {

    substitution= optimizer;

    SELECT_LEX *current= thd->lex->current_select;

    thd->lex->current_select= current->return_after_parsing();
    if (!optimizer || optimizer->fix_left(thd))
    {
      thd->lex->current_select= current;
      DBUG_RETURN(true);
    }
    thd->lex->current_select= current;


    optimizer->keep_top_level_cache();


    expr= new (thd->mem_root) Item_direct_ref(thd, &select_lex->context,
                              (Item**)optimizer->get_cache(),
			      (char *)"<no matter>",
			      (char *)in_left_expr_name);
  }

  DBUG_RETURN(false);
}
