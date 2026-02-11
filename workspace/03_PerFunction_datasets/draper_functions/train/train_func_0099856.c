ippSetString(ipp_t           *ipp,
             ipp_attribute_t **attr,
             int             element,
	     const char      *strvalue)
{
  char		*temp;
  _ipp_value_t	*value;


  if (!ipp || !attr || !*attr ||
      ((*attr)->value_tag != IPP_TAG_TEXTLANG &&
      (*attr)->value_tag != IPP_TAG_NAMELANG &&
       ((*attr)->value_tag < IPP_TAG_TEXT ||
        (*attr)->value_tag > IPP_TAG_MIMETYPE)) ||
      element < 0 || element > (*attr)->num_values || !strvalue)
    return (0);


  if ((value = ipp_set_value(ipp, attr, element)) != NULL)
  {
    if (element > 0)
      value->string.language = (*attr)->values[0].string.language;

    if ((int)((*attr)->value_tag) & IPP_TAG_CUPS_CONST)
      value->string.text = (char *)strvalue;
    else if ((temp = _cupsStrAlloc(strvalue)) != NULL)
    {
      if (value->string.text)
        _cupsStrFree(value->string.text);

      value->string.text = temp;
    }
    else
      return (0);
  }

  return (value != NULL);
}
