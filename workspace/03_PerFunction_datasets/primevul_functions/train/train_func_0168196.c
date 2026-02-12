parse_strict_transport_security (const char *header, time_t *max_age, bool *include_subdomains)
{
  param_token name, value;
  const char *c_max_age = NULL;
  bool is = false;
  bool is_url_encoded = false;
  bool success = false;

  if (header)
    {

      for (; extract_param (&header, &name, &value, ';', &is_url_encoded); is_url_encoded = false)
        {
          if (BOUNDED_EQUAL_NO_CASE (name.b, name.e, "max-age"))
            {
              xfree (c_max_age);
              c_max_age = strdupdelim (value.b, value.e);
            }
          else if (BOUNDED_EQUAL_NO_CASE (name.b, name.e, "includeSubDomains"))
            is = true;
        }


      if (c_max_age)
        {


          if (max_age)
            *max_age = (time_t) strtol (c_max_age, NULL, 10);
          if (include_subdomains)
            *include_subdomains = is;

          DEBUGP (("Parsed Strict-Transport-Security max-age = %s, includeSubDomains = %s\n",
                 c_max_age, (is ? "true" : "false")));

          xfree (c_max_age);
          success = true;
        }
      else
        {

          logprintf (LOG_VERBOSE, "Could not parse String-Transport-Security header\n");
          success = false;
        }
    }

  return success;
}
