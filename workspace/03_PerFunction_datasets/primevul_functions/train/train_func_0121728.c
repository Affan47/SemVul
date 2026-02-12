xml_check_first_element (GstTypeFind * tf, const gchar * element, guint elen,
    gboolean strict)
{
  gboolean got_xmldec;
  const guint8 *data;
  guint offset = 0;
  guint pos = 0;

  data = gst_type_find_peek (tf, 0, XML_BUFFER_SIZE);
  if (!data)
    return FALSE;


  got_xmldec = (memcmp (data, "<?xml", 5) == 0);

  if (strict && !got_xmldec)
    return FALSE;


  if (got_xmldec) {
    pos += 5;
    data += 5;
  }


  while (data && (offset + pos) < 4096) {
    while (*data != '<' && (offset + pos) < 4096) {
      XML_INC_BUFFER;
    }

    XML_INC_BUFFER;
    if (!g_ascii_isalpha (*data)) {


      XML_INC_BUFFER;
      continue;
    }


    data = gst_type_find_peek (tf, offset + pos, elen + 1);
    return (data && element && strncmp ((char *) data, element, elen) == 0);
  }

  return FALSE;
}
