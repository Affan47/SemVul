free_field(FIELD * field)
{
  if (!field)
    RETURN(E_BAD_ARGUMENT);

  if (field->form)
    RETURN(E_CONNECTED);

  if (field == field->link)
    {
      if (field->buf)
	free(field->buf);
    }
  else
    {
      FIELD *f;

      for(f=field;f->link != field;f = f->link)
	{}
      f->link = field->link;
    }
  _nc_Free_Type(field);
  free(field);
  RETURN(E_OK);
}
