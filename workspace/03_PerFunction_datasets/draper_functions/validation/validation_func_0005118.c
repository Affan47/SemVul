on_button_edit_calculation()
{

  Dialog_FieldCalculation* dialog = 0;
  Utils::get_glade_widget_derived_with_warning(dialog);
  if(!dialog)
    return;

  add_view(dialog);

  m_Field->set_calculation( m_pTextView_Calculation->get_buffer()->get_text() );
  dialog->set_field(m_Field, m_table_name);

  const int response = Glom::Utils::dialog_run_with_help(dialog);
  if(response == Gtk::RESPONSE_OK)
  {
    m_pTextView_Calculation->get_buffer()->set_text( dialog->get_field()->get_calculation() );
  }

  remove_view(dialog);
  delete dialog;
}
