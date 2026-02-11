ipmi_interpret_config_parse_strtoul (conffile_t cf,
                                     const char *str,
                                     uint32_t max,
                                     uint32_t *value)
{
  char *endptr = NULL;

  assert (cf);
  assert (str);
  assert (value);

  errno = 0;

  (*value) = strtoul (str, &endptr, 0);

  if (errno
      || endptr[0] != '\0'
      || (*value) > max)
    {
      conffile_seterrnum (cf, CONFFILE_ERR_PARSE_ARG_INVALID);
      return (-1);
    }

  return (0);
}
