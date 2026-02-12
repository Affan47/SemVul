int subselect_partial_match_engine::exec()
{
  Item_in_subselect *item_in= (Item_in_subselect *) item;
  int lookup_res;

  DBUG_ASSERT(!(item_in->left_expr_has_null() &&
                item_in->is_top_level_item()));

  if (!item_in->left_expr_has_null())
  {

    if (lookup_engine->copy_ref_key(false))
    {

      item_in->value= 0;
      item_in->null_value= 0;
      return 0;
    }
    else
    {

      if ((lookup_res= lookup_engine->index_lookup()))
      {

        item_in->value= 0;
        item_in->null_value= 0;
        return lookup_res;
      }
      else if (item_in->value || !count_columns_with_nulls)
      {


        return 0;
      }
    }
  }

  if (has_covering_null_row)
  {


    item_in->value= 0;


    item_in->null_value= 1;
    return 0;
  }


  if (tmp_table->file->inited)
    tmp_table->file->ha_index_end();

  if (partial_match())
  {

    item_in->value= 0;


    item_in->null_value= 1;
  }
  else
  {

    item_in->value= 0;


    item_in->null_value= 0;
  }

  return 0;
}
