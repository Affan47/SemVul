get_row(const Gnome::Gda::Value& key)
{
  if(!m_refListStore)
    return Gtk::TreeModel::iterator();

  for(Gtk::TreeModel::iterator iter = m_refListStore->children().begin(); iter != m_refListStore->children().end(); ++iter)
  {

    const Gnome::Gda::Value& valTemp = get_value_key(iter);
    if(valTemp == key)
    {
      return iter;
    }
  }

  return  m_refListStore->children().end();
}
