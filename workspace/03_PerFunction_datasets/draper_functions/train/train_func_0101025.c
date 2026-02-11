parse_hex (GeglColor   *color,
           const gchar *color_string)
{
  gint              i;
  gsize             string_length = strlen (color_string);

  if (string_length == 7 ||
      string_length == 9)
    {
      gint num_iterations = (string_length - 1) / 2;
      for (i = 0; i < num_iterations; ++i)
        {
          if (g_ascii_isxdigit (color_string[2 * i + 1]) &&
              g_ascii_isxdigit (color_string[2 * i + 2]))
            {
              color->priv->rgba_color[i] = (g_ascii_xdigit_value (color_string[2 * i + 1]) << 4 |
                                     g_ascii_xdigit_value (color_string[2 * i + 2])) / 255.f;
            }
          else
            {
              return FALSE;
            }
        }


      return TRUE;
    }
  else if (string_length == 4 ||
           string_length == 5)
    {
      gint num_iterations = string_length - 1;
      for (i = 0; i < num_iterations; ++i)
        {
          if (g_ascii_isxdigit (color_string[i + 1]))
            {
              color->priv->rgba_color[i] = (g_ascii_xdigit_value (color_string[i + 1]) << 4 |
                                     g_ascii_xdigit_value (color_string[i + 1])) / 255.f;
            }
          else
            {
              return FALSE;
            }
        }


      return TRUE;
    }


  return FALSE;
}
