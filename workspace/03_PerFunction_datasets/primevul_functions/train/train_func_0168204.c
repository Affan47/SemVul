parse_content_disposition (const char *hdr, char **filename)
{
  param_token name, value;
  bool is_url_encoded = false;

  char *encodedFilename = NULL;
  char *unencodedFilename = NULL;
  for ( ; extract_param (&hdr, &name, &value, ';', &is_url_encoded);
        is_url_encoded = false)
    {
      int isFilename = BOUNDED_EQUAL_NO_CASE (name.b, name.e, "filename");
      if ( isFilename && value.b != NULL)
        {

          bool isEncodedFilename;
          char **outFilename;
          const char *last_slash = memrchr (value.b, '/', value.e - value.b);
          const char *last_bs = memrchr (value.b, '\\', value.e - value.b);
          if (last_slash && last_bs)
            value.b = 1 + MAX (last_slash, last_bs);
          else if (last_slash || last_bs)
            value.b = 1 + (last_slash ? last_slash : last_bs);
          if (value.b == value.e)
            continue;


          isEncodedFilename = *name.e == '*' && !c_isdigit (*(name.e + 1));
          outFilename = isEncodedFilename ? &encodedFilename
            : &unencodedFilename;
          if (*outFilename)
            append_value_to_filename (outFilename, &value, is_url_encoded);
          else
            {
              *outFilename = strdupdelim (value.b, value.e);
              if (is_url_encoded)
                url_unescape (*outFilename);
            }
        }
    }
  if (encodedFilename)
    {
      xfree (unencodedFilename);
      *filename = encodedFilename;
    }
  else
    {
      xfree (encodedFilename);
      *filename = unencodedFilename;
    }
  if (*filename)
    return true;
  else
    return false;
}
