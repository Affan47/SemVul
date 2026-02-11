on_button_edit_field()
{
  Glib::RefPtr<Gtk::TreeView::Selection> refTreeSelection = m_treeview_fields->get_selection();
  if(refTreeSelection)
  {

    Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
    if(iter)
    {
      Gtk::TreeModel::Row row = *iter;
      sharedptr<const LayoutItem_Field> field = row[m_ColumnsFields.m_col_layout_item];


      sharedptr<LayoutItem_Field> field_chosen =
        offer_field_list_select_one_field(field, m_table_name, this);


      if(field_chosen)
        row[m_ColumnsFields.m_col_layout_item] = field_chosen;


    }
  }
}
