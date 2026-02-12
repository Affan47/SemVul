parse_line (guint8 * buffer, GstRTSPMessage * msg)
{
  GstRTSPHeaderField field;
  gchar *line = (gchar *) buffer;
  gchar *field_name = NULL;
  gchar *value;

  if ((value = strchr (line, ':')) == NULL || value == line)
    goto parse_error;


  if (value[-1] == ' ')
    value[-1] = '\0';


  *value++ = '\0';


  field = gst_rtsp_find_header_field (line);

  if (field == GST_RTSP_HDR_INVALID)
    field_name = line;


  while (*value != '\0') {
    gchar *next_value;
    gchar *comma = NULL;
    gboolean quoted = FALSE;
    guint comment = 0;


    if (*value == ' ')
      value++;


    if (!gst_rtsp_header_allow_multiple (field))
      next_value = value + strlen (value);
    else
      next_value = value;


    while (*next_value != '\0') {
      if ((quoted || comment != 0) && *next_value == '\\' &&
          next_value[1] != '\0')
        next_value++;
      else if (comment == 0 && *next_value == '"')
        quoted = !quoted;
      else if (!quoted && *next_value == '(')
        comment++;
      else if (comment != 0 && *next_value == ')')
        comment--;
      else if (!quoted && comment == 0) {


        if (field == GST_RTSP_HDR_PROXY_AUTHENTICATE ||
            field == GST_RTSP_HDR_WWW_AUTHENTICATE) {
          if (*next_value == ',') {
            if (next_value[1] == ' ') {


              next_value++;
            }
            comma = next_value;
          } else if (*next_value == ' ' && next_value[1] != ',' &&
              next_value[1] != '=' && comma != NULL) {
            next_value = comma;
            comma = NULL;
            break;
          }
        } else if (*next_value == ',')
          break;
      }

      next_value++;
    }

    if (msg->type == GST_RTSP_MESSAGE_REQUEST && field == GST_RTSP_HDR_SESSION) {


      next_value = value;
      while (*next_value != '\0') {
        if (*next_value == ';') {
          break;
        }
        next_value++;
      }
    }


    if (value != next_value && next_value[-1] == ' ')
      next_value[-1] = '\0';

    if (*next_value != '\0')
      *next_value++ = '\0';


    if (*value != '\0') {
      if (field != GST_RTSP_HDR_INVALID)
        gst_rtsp_message_add_header (msg, field, value);
      else
        gst_rtsp_message_add_header_by_name (msg, field_name, value);
    }

    value = next_value;
  }

  return GST_RTSP_OK;


parse_error:
  {
    return GST_RTSP_EPARSE;
  }
}
