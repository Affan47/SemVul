on_combo_lookup_relationship_changed()
{


  m_pCombo_LookupField->remove_all();


  sharedptr<const Relationship> relationship = m_pCombo_LookupRelationship->get_selected_relationship();
  if(relationship)
  {

    Document* document = dynamic_cast<Document*>(get_document());
    if(document)
    {
      const Glib::ustring to_table = relationship->get_to_table();
      if(!to_table.empty())
      {

        const type_vec_fields fields_in_to_table = DbUtils::get_fields_for_table(document, to_table);
        for(type_vec_fields::const_iterator iter = fields_in_to_table.begin(); iter != fields_in_to_table.end(); ++iter)
        {
          m_pCombo_LookupField->append((*iter)->get_name());
        }
      }
    }
  }

}
