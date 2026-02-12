static bool check_simple_equality(THD *thd, const Item::Context &ctx,
                                  Item *left_item, Item *right_item,
                                  COND_EQUAL *cond_equal)
{
  Item *orig_left_item= left_item;
  Item *orig_right_item= right_item;
  if (left_item->type() == Item::REF_ITEM &&
      ((Item_ref*)left_item)->ref_type() == Item_ref::VIEW_REF)
  {
    if (((Item_ref*)left_item)->get_depended_from())
      return FALSE;
    if (((Item_direct_view_ref*)left_item)->get_null_ref_table() !=
        NO_NULL_TABLE && !left_item->real_item()->used_tables())
      return FALSE;
    left_item= left_item->real_item();
  }
  if (right_item->type() == Item::REF_ITEM &&
      ((Item_ref*)right_item)->ref_type() == Item_ref::VIEW_REF)
  {
    if (((Item_ref*)right_item)->get_depended_from())
      return FALSE;
    if (((Item_direct_view_ref*)right_item)->get_null_ref_table() !=
        NO_NULL_TABLE && !right_item->real_item()->used_tables())
      return FALSE;
    right_item= right_item->real_item();
  }
  if (left_item->type() == Item::FIELD_ITEM &&
      right_item->type() == Item::FIELD_ITEM &&
      !((Item_field*)left_item)->get_depended_from() &&
      !((Item_field*)right_item)->get_depended_from())
  {


    Field *left_field= ((Item_field*) left_item)->field;
    Field *right_field= ((Item_field*) right_item)->field;

    if (!left_field->eq_def(right_field))
      return FALSE;


    bool left_copyfl, right_copyfl;
    Item_equal *left_item_equal=
               find_item_equal(cond_equal, left_field, &left_copyfl);
    Item_equal *right_item_equal=
               find_item_equal(cond_equal, right_field, &right_copyfl);


    if (left_field->eq(right_field))
      return (!(left_field->maybe_null() && !left_item_equal));

    if (left_item_equal && left_item_equal == right_item_equal)
    {


       return TRUE;
    }


    if (left_copyfl)
    {

      left_item_equal= new (thd->mem_root) Item_equal(thd, left_item_equal);
      left_item_equal->set_context_field(((Item_field*) left_item));
      cond_equal->current_level.push_back(left_item_equal, thd->mem_root);
    }
    if (right_copyfl)
    {

      right_item_equal= new (thd->mem_root) Item_equal(thd, right_item_equal);
      right_item_equal->set_context_field(((Item_field*) right_item));
      cond_equal->current_level.push_back(right_item_equal, thd->mem_root);
    }

    if (left_item_equal)
    {

      if (! right_item_equal)
        left_item_equal->add(orig_right_item, thd->mem_root);
      else
      {

        left_item_equal->merge(thd, right_item_equal);

        List_iterator<Item_equal> li(cond_equal->current_level);
        while ((li++) != right_item_equal) ;
        li.remove();
      }
    }
    else
    {

      if (right_item_equal)
        right_item_equal->add(orig_left_item, thd->mem_root);
      else
      {

        Item_equal *item_equal= new (thd->mem_root) Item_equal(thd,
                                                               orig_left_item,
                                                               orig_right_item,
                                                               FALSE);
        item_equal->set_context_field((Item_field*)left_item);
        cond_equal->current_level.push_back(item_equal, thd->mem_root);
      }
    }
    return TRUE;
  }

  {

    Item *const_item= 0;
    Item_field *field_item= 0;
    Item *orig_field_item= 0;
    if (left_item->type() == Item::FIELD_ITEM &&
        !((Item_field*)left_item)->get_depended_from() &&
        right_item->const_item() && !right_item->is_expensive())
    {
      orig_field_item= orig_left_item;
      field_item= (Item_field *) left_item;
      const_item= right_item;
    }
    else if (right_item->type() == Item::FIELD_ITEM &&
             !((Item_field*)right_item)->get_depended_from() &&
             left_item->const_item() && !left_item->is_expensive())
    {
      orig_field_item= orig_right_item;
      field_item= (Item_field *) right_item;
      const_item= left_item;
    }

    if (const_item &&
        field_item->field->test_if_equality_guarantees_uniqueness(const_item))
    {


      bool copyfl;

      Item_equal *item_equal = find_item_equal(cond_equal,
                                               field_item->field, &copyfl);
      if (copyfl)
      {
        item_equal= new (thd->mem_root) Item_equal(thd, item_equal);
        cond_equal->current_level.push_back(item_equal, thd->mem_root);
        item_equal->set_context_field(field_item);
      }
      Item *const_item2= field_item->field->get_equal_const_item(thd, ctx,
                                                                 const_item);
      if (!const_item2)
        return false;

      if (item_equal)
      {


        item_equal->add_const(thd, const_item2);
      }
      else
      {
        item_equal= new (thd->mem_root) Item_equal(thd, const_item2,
                                                   orig_field_item, TRUE);
        item_equal->set_context_field(field_item);
        cond_equal->current_level.push_back(item_equal, thd->mem_root);
      }
      return TRUE;
    }
  }
  return FALSE;
}
