CDRAG_drag(CWIDGET *source, GB_VARIANT_VALUE *data, char *format)
{
  if (GB.CheckObject(source))
    return NULL;

	if (gDrag::isActive())
	{
		GB.Error("Undergoing drag");
		return NULL;
	}

  if (data->type == GB_T_STRING)
  {
  	if (format)
  	{
  		if (strlen(format) < 5)
  			goto _BAD_FORMAT;
  		if (strncasecmp(format, "text/", 5))
        goto _BAD_FORMAT;
    }

    gDrag::dragText(source->widget, data->value._string, format);
  }
  else if (data->type >= GB_T_OBJECT && GB.Is(data->value._object, GB.FindClass("Image")))
  {
    if (format && *format)
      goto _BAD_FORMAT;

		gDrag::dragImage(source->widget, CIMAGE_get((CIMAGE *)data->value._object));
  }
  else
    goto _BAD_FORMAT;


  return GetObject(gDrag::getDestination());

_BAD_FORMAT:

  GB.Error("Bad drag format");
  return NULL;
}
