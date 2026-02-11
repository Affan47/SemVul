get_value_as_bool(const Gtk::TreeModel::iterator& iter, guint col)
{

  Glib::ustring strValue = get_value(iter, col);
  return (strValue == "true");
}
