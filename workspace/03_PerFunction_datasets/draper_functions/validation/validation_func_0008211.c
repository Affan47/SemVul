import_config (const ACE_TCHAR* filename)
{
  if (0 == filename)
    {
      errno = EINVAL;
      return -1;
    }
  FILE* in = ACE_OS::fopen (filename, ACE_TEXT ("r"));
  if (!in)
    return -1;


  ACE_TCHAR buffer[4096];
  ACE_Configuration_Section_Key section;
  while (ACE_OS::fgets (buffer, sizeof buffer, in))
    {
      ACE_TCHAR *line = this->squish (buffer);

      if (line[0] == ACE_TEXT (';')  ||
          line[0] == ACE_TEXT ('#')  ||
          line[0] == '\0')
        continue;

      if (line[0] == ACE_TEXT ('['))
        {

          ACE_TCHAR* end = ACE_OS::strrchr (line, ACE_TEXT (']'));
          if (!end)
            {
              ACE_OS::fclose (in);
              return -3;
            }
          *end = 0;

          if (config_.expand_path (config_.root_section (),
                                   line + 1,
                                   section,
                                   1))
            {
              ACE_OS::fclose (in);
              return -3;
            }

          continue;
        }


      ACE_TCHAR *end = ACE_OS::strchr (line, ACE_TEXT ('='));
      if (end == 0)
        {
          ACE_OS::fclose (in);
          return -3;
        }
      *end++ = '\0';
      ACE_TCHAR *name = this->squish (line);
#if 0
      if (ACE_OS::strlen (name) == 0)
        {
          ACE_OS::fclose (in);
          return -3;
        }
#endif

      ACE_TCHAR *value = this->squish (end);
      size_t value_len = ACE_OS::strlen (value);
      if (value_len > 0)
        {


          if (value[0] == ACE_TEXT ('"') &&
              value[value_len - 1] == ACE_TEXT ('"'))
            {

              value[value_len - 1] = '\0';
              ++value;
            }
        }

      if (config_.set_string_value (section, name, value))
        {
          ACE_OS::fclose (in);
          return -4;
        }
    }

  if (ferror (in))
    {
      ACE_OS::fclose (in);
      return -1;
    }

  ACE_OS::fclose (in);
  return 0;
}
