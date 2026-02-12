void Item_field::update_null_value()
{


  THD *thd= field->table->in_use;
  int no_errors;

  no_errors= thd->no_errors;
  thd->no_errors= 1;
  Item::update_null_value();
  thd->no_errors= no_errors;
}
