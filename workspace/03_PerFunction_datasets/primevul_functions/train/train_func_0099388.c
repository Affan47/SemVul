g_markup_vprintf_escaped (const gchar *format,
                          va_list      args)
{
  GString *format1;
  GString *format2;
  GString *result = NULL;
  gchar *output1 = NULL;
  gchar *output2 = NULL;
  const char *p, *op1, *op2;
  va_list args2;


  format1 = g_string_new (NULL);
  format2 = g_string_new (NULL);
  p = format;
  while (TRUE)
    {
      const char *after;
      const char *conv = find_conversion (p, &after);
      if (!conv)
        break;

      g_string_append_len (format1, conv, after - conv);
      g_string_append_c (format1, 'X');
      g_string_append_len (format2, conv, after - conv);
      g_string_append_c (format2, 'Y');

      p = after;
    }


  G_VA_COPY (args2, args);

  output1 = g_strdup_vprintf (format1->str, args);

  if (!output1)
    {
      va_end (args2);
      goto cleanup;
    }

  output2 = g_strdup_vprintf (format2->str, args2);
  va_end (args2);
  if (!output2)
    goto cleanup;
  result = g_string_new (NULL);


  op1 = output1;
  op2 = output2;
  p = format;
  while (TRUE)
    {
      const char *after;
      const char *output_start;
      const char *conv = find_conversion (p, &after);
      char *escaped;

      if (!conv)
        {
          g_string_append_len (result, p, after - p);
          break;
        }

      g_string_append_len (result, p, conv - p);
      output_start = op1;
      while (*op1 == *op2)
        {
          op1++;
          op2++;
        }

      escaped = g_markup_escape_text (output_start, op1 - output_start);
      g_string_append (result, escaped);
      g_free (escaped);

      p = after;
      op1++;
      op2++;
    }

 cleanup:
  g_string_free (format1, TRUE);
  g_string_free (format2, TRUE);
  g_free (output1);
  g_free (output2);

  if (result)
    return g_string_free (result, FALSE);
  else
    return NULL;
}
