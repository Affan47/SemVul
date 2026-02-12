Item_in_subselect::row_value_transformer(JOIN *join)
{
  SELECT_LEX *select_lex= join->select_lex;
  uint cols_num= left_expr->cols();

  DBUG_ENTER("Item_in_subselect::row_value_transformer");
  DBUG_ASSERT(thd == join->thd);


  if (select_lex->item_list.elements != cols_num)
  {
    my_error(ER_OPERAND_COLUMNS, MYF(0), cols_num);
    DBUG_RETURN(true);
  }


  if (!substitution)
  {

    SELECT_LEX_UNIT *master_unit= select_lex->master_unit();
    substitution= optimizer;

    SELECT_LEX *current= thd->lex->current_select;
    thd->lex->current_select= current->return_after_parsing();
    if (!optimizer || optimizer->fix_left(thd))
    {
      thd->lex->current_select= current;
      DBUG_RETURN(true);
    }


    optimizer->keep_top_level_cache();

    thd->lex->current_select= current;


    master_unit->uncacheable|= UNCACHEABLE_EXPLAIN;
    select_lex->uncacheable|= UNCACHEABLE_EXPLAIN;
  }

  DBUG_RETURN(false);
}
