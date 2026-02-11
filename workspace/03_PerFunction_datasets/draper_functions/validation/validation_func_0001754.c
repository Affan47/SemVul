take_static_value(const Value& value, bool& value_changed)
{
  GError* gerror = 0;
  Value retvalue = Value(gda_holder_take_static_value(gobj(), (value).gobj(), (gboolean*)(&(value_changed)), &(gerror)));
  if(gerror)
    ::Glib::Error::throw_exception(gerror);

  return retvalue;

}
