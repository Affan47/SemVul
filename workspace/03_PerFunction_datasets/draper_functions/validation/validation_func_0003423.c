user_requested_delete(const Gtk::TreeModel::iterator& rowStart, const Gtk::TreeModel::iterator&  )
{
  if(rowStart)
  {
    if(confirm_delete_record())
    {
      const Gnome::Gda::Value primary_key_value = get_primary_key_value(rowStart);
      if(!m_find_mode)
        record_delete(primary_key_value);


      remove_item(rowStart);


      on_record_deleted(primary_key_value);
    }
  }
}
