xml_check_first_element_from_data (const guint8 * data, guint length,
    const gchar * element, guint elen, gboolean strict)
{
  gboolean got_xmldec;
  guint pos = 0;

  g_return_val_if_fail (data != NULL, FALSE);

  if (length <= 5)
    return FALSE;


  got_xmldec = (memcmp (data, "<?xml", 5) == 0);

  if (strict && !got_xmldec)
    return FALSE;


  if (got_xmldec) {
    pos += 5;
    data += 5;
  }


  while (pos < MIN (4096, length)) {
    while (*data != '<' && pos < MIN (4096, length)) {
      XML_INC_BUFFER_DATA;
    }

    XML_INC_BUFFER_DATA;
    if (!g_ascii_isalpha (*data)) {


      XML_INC_BUFFER_DATA;
      continue;
    }


    if (pos + elen + 1 >= length)
      return FALSE;
    return (element && strncmp ((const char *) data, element, elen) == 0);
  }

  return FALSE;
}
