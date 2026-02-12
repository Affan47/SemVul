Item_in_subselect::select_in_like_transformer(JOIN *join)
{
  Query_arena *arena= 0, backup;
  SELECT_LEX *current= thd->lex->current_select;
  const char *save_where= thd->where;
  bool trans_res= true;
  bool result;

  DBUG_ENTER("Item_in_subselect::select_in_like_transformer");
  DBUG_ASSERT(thd == join->thd);


  for (SELECT_LEX *sl= current->master_unit()->first_select();
       sl; sl= sl->next_select())
  {
    if (sl->join)
    {
      sl->join->order= 0;
      sl->join->skip_sort_order= 1;
    }
  }

  thd->where= "IN/ALL/ANY subquery";


  arena= thd->activate_stmt_arena_if_needed(&backup);
  if (!optimizer)
  {
    optimizer= new (thd->mem_root) Item_in_optimizer(thd, left_expr_orig, this);
    if ((result= !optimizer))
      goto out;
  }

  thd->lex->current_select= current->return_after_parsing();
  result= optimizer->fix_left(thd);
  thd->lex->current_select= current;

  if (changed)
  {
    trans_res= false;
    goto out;
  }


  if (result)
    goto out;


  if (left_expr->cols() == 1)
    trans_res= single_value_transformer(join);
  else
  {

    if (func != &eq_creator)
    {
      if (arena)
        thd->restore_active_arena(arena, &backup);
      my_error(ER_OPERAND_COLUMNS, MYF(0), 1);
      DBUG_RETURN(true);
    }
    trans_res= row_value_transformer(join);
  }
out:
  if (arena)
    thd->restore_active_arena(arena, &backup);
  thd->where= save_where;
  DBUG_RETURN(trans_res);
}
