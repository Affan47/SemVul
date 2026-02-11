Field_encloses(FIELD *field, int ry, int rx)
{
  T((T_CALLED("Field_encloses(%p)"), field));
  if (field != 0
      && field->frow <= ry
      && (field->frow + field->rows) > ry
      && field->fcol <= rx
      && (field->fcol + field->cols) > rx)
    {
      RETURN(E_OK);
    }
  RETURN(E_INVALID_FIELD);
}
