host_address_extract_port(uschar *address)
{
int port = 0;
uschar *endptr;


if (*address == '[')
  {
  uschar *rb = address + 1;
  while (*rb != 0 && *rb != ']') rb++;
  if (*rb++ == 0) return 0;
  if (*rb == ':')
    {
    port = Ustrtol(rb + 1, &endptr, 10);
    if (*endptr != 0) return 0;
    }
  else if (*rb != 0) return 0;
  memmove(address, address + 1, rb - address - 2);
  rb[-2] = 0;
  }


else
  {
  int skip = -3;
  address--;
  while (*(++address) != 0)
    {
    int ch = *address;
    if (ch == ':') skip = 0;
      else if (ch == '.' && skip++ >= 0) break;
    }
  if (*address == 0) return 0;
  port = Ustrtol(address + 1, &endptr, 10);
  if (*endptr != 0) return 0;
  *address = 0;
  }

return port;
}
