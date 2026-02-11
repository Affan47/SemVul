get_table_used(const Glib::ustring& parent_table) const
{


  if(m_related_relationship)
    return m_related_relationship->get_to_table();
  else if(m_relationship)
    return m_relationship->get_to_table();
  else
    return parent_table;
}
