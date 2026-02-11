tor_addr_port_lookup(const char *s, tor_addr_t *addr_out, uint16_t *port_out)
{
  const char *port;
  tor_addr_t addr;
  uint16_t portval;
  char *tmp = NULL;

  tor_assert(s);
  tor_assert(addr_out);

  s = eat_whitespace(s);

  if (*s == '[') {
    port = strstr(s, "]");
    if (!port)
      goto err;
    tmp = tor_strndup(s+1, port-(s+1));
    port = port+1;
    if (*port == ':')
      port++;
    else
      port = NULL;
  } else {
    port = strchr(s, ':');
    if (port)
      tmp = tor_strndup(s, port-s);
    else
      tmp = tor_strdup(s);
    if (port)
      ++port;
  }

  if (tor_addr_lookup(tmp, AF_UNSPEC, &addr) != 0)
    goto err;
  tor_free(tmp);

  if (port) {
    portval = (int) tor_parse_long(port, 10, 1, 65535, NULL, NULL);
    if (!portval)
      goto err;
  } else {
    portval = 0;
  }

  if (port_out)
    *port_out = portval;
  tor_addr_copy(addr_out, &addr);

  return 0;
 err:
  tor_free(tmp);
  return -1;
}
