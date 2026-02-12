enum_field_types Item_type_holder::get_real_type(Item *item)
{
  if (item->type() == REF_ITEM)
    item= item->real_item();
  switch(item->type())
  {
  case FIELD_ITEM:
  {


    Field *field= ((Item_field *) item)->field;
    enum_field_types type= field->real_type();
    if (field->is_created_from_null_item)
      return MYSQL_TYPE_NULL;

    if (type == MYSQL_TYPE_STRING && field->type() == MYSQL_TYPE_VAR_STRING)
      return MYSQL_TYPE_VAR_STRING;
    return type;
  }
  case SUM_FUNC_ITEM:
  {


    Item_sum *item_sum= (Item_sum *) item;
    if (item_sum->keep_field_type())
      return get_real_type(item_sum->get_arg(0));
    break;
  }
  case FUNC_ITEM:
    if (((Item_func *) item)->functype() == Item_func::GUSERVAR_FUNC)
    {


      switch (item->result_type()) {
      case STRING_RESULT:
        return MYSQL_TYPE_VAR_STRING;
      case INT_RESULT:
        return MYSQL_TYPE_LONGLONG;
      case REAL_RESULT:
        return MYSQL_TYPE_DOUBLE;
      case DECIMAL_RESULT:
        return MYSQL_TYPE_NEWDECIMAL;
      case ROW_RESULT:
      case TIME_RESULT:
      case IMPOSSIBLE_RESULT:
        DBUG_ASSERT(0);
        return MYSQL_TYPE_VAR_STRING;
      }
    }
    break;
  default:
    break;
  }
  return item->field_type();
}
