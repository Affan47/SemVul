on_button_formatting()
{


  Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = m_treeview_fields->get_selection();
  if(refTreeSelection)
  {
    Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
    if(iter)
    {
      Gtk::TreeModel::Row row = *iter;

      sharedptr<LayoutItem> layout_item = row[m_model_items->m_columns.m_col_layout_item];
      sharedptr<LayoutItem_Field> field = sharedptr<LayoutItem_Field>::cast_dynamic(layout_item);
      if(field)
      {

        sharedptr<LayoutItem_Field> chosenitem = offer_field_formatting(field, get_fields_table(), this, m_editable_layout);
        if(chosenitem)
        {
          *field = *chosenitem;
          m_modified = true;

        }
      }
      else
      {

        sharedptr<LayoutItem_WithFormatting> withformatting = sharedptr<LayoutItem_WithFormatting>::cast_dynamic(layout_item);
        if(withformatting)
        {
          const bool changed = offer_non_field_item_formatting(withformatting, this);
          if(changed)
            m_modified = true;
        }
      }
    }
  }
}
