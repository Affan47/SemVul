void Item_subselect::init(st_select_lex *select_lex,
			  select_result_interceptor *result)
{


  DBUG_ENTER("Item_subselect::init");
  DBUG_PRINT("enter", ("select_lex: %p  this: %p",
                       select_lex, this));
  unit= select_lex->master_unit();

  if (unit->item)
  {
    engine= unit->item->engine;
    parsing_place= unit->item->parsing_place;
    if (unit->item->substype() == EXISTS_SUBS &&
        ((Item_exists_subselect *)unit->item)->exists_transformed)
    {

      unit->item= this;
      engine->change_result(this, result, FALSE);
    }
    else
    {


      unit->thd->change_item_tree((Item**)&unit->item, this);
      engine->change_result(this, result, TRUE);
    }
  }
  else
  {
    SELECT_LEX *outer_select= unit->outer_select();


    parsing_place= (outer_select->in_sum_expr ? NO_MATTER
                                              : outer_select->parsing_place);
    if (unit->is_union())
      engine= new subselect_union_engine(unit, result, this);
    else
      engine= new subselect_single_select_engine(select_lex, result, this);
  }
  {
    SELECT_LEX *upper= unit->outer_select();
    if (upper->parsing_place == IN_HAVING)
      upper->subquery_in_having= 1;

    upper->expr_cache_may_be_used[upper->parsing_place]= TRUE;
  }
  DBUG_PRINT("info", ("engine: %p", engine));
  DBUG_VOID_RETURN;
}
