serialize_buffer_of_text (hb_buffer_t  *buffer,
					    unsigned int  line_no,
					    const char   *text,
					    unsigned int  text_len,
					    hb_font_t    *font,
					    GString      *gs)
{
  if (show_text) {
    serialize_line_no (line_no, gs);
    g_string_append_c (gs, '(');
    g_string_append_len (gs, text, text_len);
    g_string_append_c (gs, ')');
    g_string_append_c (gs, '\n');
  }

  if (show_unicode) {
    serialize_line_no (line_no, gs);
    serialize_unicode (buffer, gs);
    g_string_append_c (gs, '\n');
  }
}
