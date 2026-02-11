insert_text(const char *text, GtkTextTag *tag)
{
  GtkTextTag *tags[7];

  tags[0] = tags[1] = tags[2] = tags[3] = tags[4] = tags[5] = tags[6] = NULL;

  int i = 0;

  if (parse_flags & PARSE_FLAGS_BOLD)
    tags[i++] = _w.tag_bold;
  if (parse_flags & PARSE_FLAGS_ITALIC)
    tags[i++] = _w.tag_italic;
  if (parse_flags & PARSE_FLAGS_UNDERLINE)
    tags[i++] = _w.tag_underline;
  if (parse_flags & PARSE_FLAGS_CENTER)
    tags[i++] = _w.tag_center;
  if (parse_flags & PARSE_FLAGS_MONOSPACE)
    tags[i++] = _w.tag_monospace;
  if (_w.tag_size[text_size + 3] != NULL)
    tags[i++] = _w.tag_size[text_size + 3];
  if (tag != NULL)
    tags[i++] = tag;

  gtk_text_buffer_insert_with_tags(_w.text_buffer, &iter, text, -1, tags[0], tags[1], tags[2], tags[3], tags[4], tags[5], tags[6], NULL);
}
