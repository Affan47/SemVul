void Item_field::reset_field(Field *f)
{
  set_field(f);

  name= (char*) f->field_name;
}
