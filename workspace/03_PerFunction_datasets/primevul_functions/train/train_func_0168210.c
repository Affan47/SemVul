set_content_type (int *dt, const char *type)
{


  if (!type ||
      0 == c_strcasecmp (type, TEXTHTML_S) ||
      0 == c_strcasecmp (type, TEXTXHTML_S))
    *dt |= TEXTHTML;
  else
    *dt &= ~TEXTHTML;

  if (type &&
      0 == c_strcasecmp (type, TEXTCSS_S))
    *dt |= TEXTCSS;
  else
    *dt &= ~TEXTCSS;
}
