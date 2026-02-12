check_helo(uschar *s)
{
uschar *start = s;
uschar *end = s + Ustrlen(s);
BOOL yield = fl.helo_accept_junk;


if (sender_helo_name)
  {
  store_free(sender_helo_name);
  sender_helo_name = NULL;
  }


if (!yield)


  if (*s == '[')
    {
    if (end[-1] == ']')
      {
      end[-1] = 0;
      if (strncmpic(s, US"[IPv6:", 6) == 0)
        yield = (string_is_ip_address(s+6, NULL) == 6);
      else if (strncmpic(s, US"[IPv4:", 6) == 0)
        yield = (string_is_ip_address(s+6, NULL) == 4);
      else
        yield = (string_is_ip_address(s+1, NULL) != 0);
      end[-1] = ']';
      }
    }


  else if (*s)
    for (yield = TRUE; *s; s++)
      if (!isalnum(*s) && *s != '.' && *s != '-' &&
          Ustrchr(helo_allow_chars, *s) == NULL)
        {
        yield = FALSE;
        break;
        }


if (yield) sender_helo_name = string_copy_malloc(start);
return yield;
}
