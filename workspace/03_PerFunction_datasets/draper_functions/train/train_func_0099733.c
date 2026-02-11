fill_from_database()
{
  BusyCursor busy_cursor(get_app_window());

  bool result = Box_DB_Table::fill_from_database();

  Document* document = get_document();
  if(!document)
    return false;


  Document::type_vec_relationships vecRelationships = document->get_relationships(m_table_name);

  m_AddDel.remove_all();

  sharedptr<SharedConnection> sharedconnection = connect_to_server(get_app_window());
  if(sharedconnection)
  {
    Glib::RefPtr<Gnome::Gda::Connection> connection = sharedconnection->get_gda_connection();


    m_AddDel.set_column_choices(m_colFromField, util_vecStrings_from_Fields(
      DbUtils::get_fields_for_table(document, m_table_name)));

    type_vec_strings vecTableNames = document->get_table_names(false );
    type_vec_strings vecTableNames_ustring(vecTableNames.begin(), vecTableNames.end());
    m_AddDel.set_column_choices(m_colToTable, vecTableNames_ustring);


    for(Document::type_vec_relationships::iterator iter = vecRelationships.begin(); iter != vecRelationships.end(); ++iter)
    {
      sharedptr<const Relationship> relationship = *iter;
      if(relationship)
      {

        Gtk::TreeModel::iterator iterTree = m_AddDel.add_item(relationship->get_name());
        m_AddDel.set_value(iterTree, m_colName, relationship->get_name());


        m_AddDel.set_value(iterTree, m_colTitle, item_get_title(relationship));
        m_AddDel.set_value(iterTree, m_colTitleSingular, relationship->get_title_singular(AppWindow::get_current_locale()));


        m_AddDel.set_value(iterTree, m_colFromField, relationship->get_from_field());


        const Glib::ustring& strToTable = relationship->get_to_table();
        m_AddDel.set_value(iterTree, m_colToTable, strToTable);


        m_AddDel.set_value(iterTree, m_colToField, relationship->get_to_field());

        m_AddDel.set_value(iterTree, m_colAllowEdit, relationship->get_allow_edit());
        m_AddDel.set_value(iterTree, m_colAutoCreate, relationship->get_auto_create());
      }
    }
  }

  return result;
}
