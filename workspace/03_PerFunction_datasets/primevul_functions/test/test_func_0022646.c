void switch_defaults_to_nullable_trigger_fields(TABLE *table)
{
  if (!table->default_field)
    return;

  Field **trigger_field= table->field_to_fill();


  if (trigger_field != table->field)
  {
    for (Field **field_ptr= table->default_field; *field_ptr ; field_ptr++)
    {
      Field *field= (*field_ptr);
      field->default_value->expr->walk(&Item::switch_to_nullable_fields_processor, 1, trigger_field);
      *field_ptr= (trigger_field[field->field_index]);
    }
  }
}
