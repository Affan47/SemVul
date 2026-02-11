id3v2_are_digits (const gchar * chars, gint size)
{
  gint i;

  for (i = 0; i < size; i++) {
    if (!g_ascii_isdigit (chars[i]))
      return FALSE;
  }
  return TRUE;
}
