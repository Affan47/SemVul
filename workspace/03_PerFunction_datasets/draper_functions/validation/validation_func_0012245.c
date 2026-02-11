on_adddel_user_requested_edit(const Gtk::TreeModel::iterator& row)
{
  const Gnome::Gda::Value primary_key_value = m_AddDel.get_value_key(row);

  signal_user_requested_details().emit(primary_key_value);
}
