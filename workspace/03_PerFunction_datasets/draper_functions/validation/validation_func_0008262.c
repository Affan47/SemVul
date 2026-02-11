init_with_tablename(const Glib::ustring& layout_name, const Glib::ustring& layout_platform, Document* document, const Glib::ustring& from_table)
{
  if(!m_portal)
  {
    m_portal = sharedptr<LayoutItem_CalendarPortal>::create();
  }

  type_vecConstLayoutFields empty_fields;


  Dialog_Layout::init(layout_name, layout_platform, document, from_table, empty_fields);


  update_ui();
}
