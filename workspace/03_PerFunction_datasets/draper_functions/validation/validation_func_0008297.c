poppler_form_field_choice_get_text (PopplerFormField *field)
{
  GooString *tmp;

  g_return_val_if_fail (field->widget->getType () == formChoice, NULL);

  tmp = static_cast<FormWidgetChoice*>(field->widget)->getEditChoice ();
  return tmp ? _poppler_goo_string_to_utf8 (tmp) : NULL;
}
