add_holder_as_value(const Glib::ustring& id, const Gda::Value& value)
{
  Glib::RefPtr<Holder> holder = Holder::create(value.get_value_type(), id);
  holder->set_value(value);
  add_holder(holder);
}
