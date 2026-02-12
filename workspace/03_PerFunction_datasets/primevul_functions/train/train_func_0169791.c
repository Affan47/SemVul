bool Item_ref::fix_fields(THD *thd, Item **reference)
{
  enum_parsing_place place= NO_MATTER;
  DBUG_ASSERT(fixed == 0);
  SELECT_LEX *current_sel= thd->lex->current_select;

  if (set_properties_only)
  {

  }
  else if (!ref || ref == not_found_item)
  {
    DBUG_ASSERT(reference_trough_name != 0);
    if (!(ref= resolve_ref_in_select_and_group(thd, this,
                                               context->select_lex)))
      goto error;

    if (ref == not_found_item)
    {
      Name_resolution_context *last_checked_context= context;
      Name_resolution_context *outer_context= context->outer_context;
      Field *from_field;
      ref= 0;

      if (!outer_context)
      {

        my_error(ER_BAD_FIELD_ERROR,MYF(0),
                 this->full_name(), thd->where);
        goto error;
      }


      from_field= (Field*) not_found_field;

      do
      {
        SELECT_LEX *select= outer_context->select_lex;
        Item_subselect *prev_subselect_item=
          last_checked_context->select_lex->master_unit()->item;
        last_checked_context= outer_context;


        if (outer_context->resolve_in_select_list)
        {
          if (!(ref= resolve_ref_in_select_and_group(thd, this, select)))
            goto error;
          if (ref != not_found_item)
          {
            DBUG_ASSERT(*ref && (*ref)->fixed);
            prev_subselect_item->used_tables_cache|= (*ref)->used_tables();
            prev_subselect_item->const_item_cache&= (*ref)->const_item();
            break;
          }


          ref= 0;
        }

        place= prev_subselect_item->parsing_place;


        if ((place != IN_HAVING ||
             (!select->with_sum_func &&
              select->group_list.elements == 0)))
        {


          from_field= find_field_in_tables(thd, this,
                                           outer_context->
                                             first_name_resolution_table,
                                           outer_context->
                                             last_name_resolution_table,
                                           reference,
                                           IGNORE_EXCEPT_NON_UNIQUE,
                                           TRUE, TRUE);
          if (! from_field)
            goto error;
          if (from_field == view_ref_found)
          {
            Item::Type refer_type= (*reference)->type();
            prev_subselect_item->used_tables_cache|=
              (*reference)->used_tables();
            prev_subselect_item->const_item_cache&=
              (*reference)->const_item();
            DBUG_ASSERT((*reference)->type() == REF_ITEM);
            mark_as_dependent(thd, last_checked_context->select_lex,
                              context->select_lex, this,
                              ((refer_type == REF_ITEM ||
                                refer_type == FIELD_ITEM) ?
                               (Item_ident*) (*reference) :
                               0));


            return FALSE;
          }
          if (from_field != not_found_field)
          {
            if (cached_table && cached_table->select_lex &&
                outer_context->select_lex &&
                cached_table->select_lex != outer_context->select_lex)
            {


              do
              {
                outer_context= outer_context->outer_context;
                select= outer_context->select_lex;
                prev_subselect_item=
                  last_checked_context->select_lex->master_unit()->item;
                last_checked_context= outer_context;
              } while (outer_context && outer_context->select_lex &&
                       cached_table->select_lex != outer_context->select_lex);
            }
            prev_subselect_item->used_tables_cache|= from_field->table->map;
            prev_subselect_item->const_item_cache= 0;
            break;
          }
        }
        DBUG_ASSERT(from_field == not_found_field);


        prev_subselect_item->used_tables_cache|= OUTER_REF_TABLE_BIT;
        prev_subselect_item->const_item_cache= 0;

        outer_context= outer_context->outer_context;
      } while (outer_context);

      DBUG_ASSERT(from_field != 0 && from_field != view_ref_found);
      if (from_field != not_found_field)
      {
        Item_field* fld;
        if (!(fld= new Item_field(from_field)))
          goto error;
        thd->change_item_tree(reference, fld);
        mark_as_dependent(thd, last_checked_context->select_lex,
                          current_sel, fld, fld);


        if (thd->lex->in_sum_func &&
            thd->lex->in_sum_func->nest_level >=
            last_checked_context->select_lex->nest_level)
          set_if_bigger(thd->lex->in_sum_func->max_arg_level,
                        last_checked_context->select_lex->nest_level);
        return FALSE;
      }
      if (ref == 0)
      {

        my_error(ER_BAD_FIELD_ERROR, MYF(0),
                 this->full_name(), thd->where);
        goto error;
      }

      DBUG_ASSERT(*ref && (*ref)->fixed);
      mark_as_dependent(thd, last_checked_context->select_lex,
                        context->select_lex, this, this);


      if (thd->lex->in_sum_func &&
          thd->lex->in_sum_func->nest_level >=
          last_checked_context->select_lex->nest_level)
        set_if_bigger(thd->lex->in_sum_func->max_arg_level,
                      last_checked_context->select_lex->nest_level);
    }
  }
  else if (ref_type() != VIEW_REF)
  {


    Dependency_marker dep_marker;
    dep_marker.current_select= current_sel;
    dep_marker.thd= thd;
    (*ref)->walk(&Item::enumerate_field_refs_processor, FALSE,
                 (uchar*)&dep_marker);
  }

  DBUG_ASSERT(*ref);


  if (!((*ref)->type() == REF_ITEM &&
       ((Item_ref *)(*ref))->ref_type() == OUTER_REF) &&
      (((*ref)->with_sum_func && name &&
        !(current_sel->linkage != GLOBAL_OPTIONS_TYPE &&
          current_sel->having_fix_field)) ||
       !(*ref)->fixed))
  {
    my_error(ER_ILLEGAL_REFERENCE, MYF(0),
             name, ((*ref)->with_sum_func?
                    "reference to group function":
                    "forward reference in item list"));
    goto error;
  }

  set_properties();

  if ((*ref)->check_cols(1))
    goto error;
  return FALSE;

error:
  context->process_error(thd);
  return TRUE;
}
