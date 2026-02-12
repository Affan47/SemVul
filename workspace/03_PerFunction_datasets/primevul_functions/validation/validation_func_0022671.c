bool test_if_ref(Item *root_cond, Item_field *left_item,Item *right_item)
{
  Field *field=left_item->field;
  JOIN_TAB *join_tab= field->table->reginfo.join_tab;

  if (!field->table->const_table && join_tab &&
      !join_tab->is_ref_for_hash_join() &&
      (!join_tab->first_inner ||
       *join_tab->first_inner->on_expr_ref == root_cond))
  {


    if (join_tab->ref.is_access_triggered())
      return FALSE;

    Item *ref_item=part_of_refkey(field->table,field);
    if (ref_item && (ref_item->eq(right_item,1) ||
		     ref_item->real_item()->eq(right_item,1)))
    {
      right_item= right_item->real_item();
      if (right_item->type() == Item::FIELD_ITEM)
	return (field->eq_def(((Item_field *) right_item)->field));

      else if (right_item->type() == Item::CACHE_ITEM)
        return ((Item_cache *)right_item)->eq_def (field);
      if (right_item->const_item() && !(right_item->is_null()))
      {


	if (field->binary() &&
	    field->real_type() != MYSQL_TYPE_STRING &&
	    field->real_type() != MYSQL_TYPE_VARCHAR &&
	    (field->type() != MYSQL_TYPE_FLOAT || field->decimals() == 0))
	{
	  return !right_item->save_in_field_no_warnings(field, 1);
	}
      }
    }
  }
  return 0;
}
