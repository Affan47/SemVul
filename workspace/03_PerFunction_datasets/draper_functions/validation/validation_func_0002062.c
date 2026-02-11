get_sql_type() const
{
  if(false)
    return "serial";
  else
  {
    Glib::ustring result;


    Glib::ustring strType = "unknowntype";

    ConnectionPool* pConnectionPool = ConnectionPool::get_instance();
    if(pConnectionPool)
    {
      const FieldTypes* pFieldTypes = pConnectionPool->get_field_types();
      if(pFieldTypes)
      {
        const GType fieldType = m_field_info->get_g_type();
        strType = pFieldTypes->get_string_name_for_gdavaluetype(fieldType);
      }
      else
      {
        std::cerr << G_STRFUNC << ": get_field_types() returned null" << std::endl;
      }
    }

    if(strType == "unknowntype")
    {
      std::cerr << G_STRFUNC << ": returning unknowntype for field name=" << get_name() << ", glom_type=" << get_glom_type() << ", gda_type=" << (int)m_field_info->get_g_type() << std::endl;
    }

    return strType;
  }
}
