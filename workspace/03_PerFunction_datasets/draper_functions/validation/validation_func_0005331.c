set_layout_groups(Document::type_list_layout_groups& mapGroups, Document* document, const Glib::ustring& table_name)
{
  Base_DB::set_document(document);

  m_modified = false;


  m_table_name = table_name;


  if(document)
  {

    m_label_table_name->set_text(table_name);

    if(document)
      document->fill_layout_field_details(m_table_name, mapGroups);


    m_model_fields->clear();

    guint field_sequence = 1;
    for(Document::type_list_layout_groups::const_iterator iter = mapGroups.begin(); iter != mapGroups.end(); ++iter)
    {
      sharedptr<const LayoutGroup> group = *iter;
      if(!group)
        continue;


      LayoutGroup::type_list_const_items items = group->get_items();
      for(LayoutGroup::type_list_const_items::const_iterator iter = items.begin(); iter != items.end(); ++iter)
      {
        sharedptr<const LayoutItem_Field> item = sharedptr<const LayoutItem_Field>::cast_dynamic(*iter);
        if(item)
        {
          Gtk::TreeModel::iterator iterTree = m_model_fields->append();
          Gtk::TreeModel::Row row = *iterTree;

          row[m_ColumnsFields.m_col_layout_item] = glom_sharedptr_clone(item);
          row[m_ColumnsFields.m_col_sequence] = field_sequence;
          ++field_sequence;
        }
      }
    }

    treeview_fill_sequences(m_model_fields, m_ColumnsFields.m_col_sequence);
  }

  m_modified = false;
}
