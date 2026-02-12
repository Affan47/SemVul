transport_set_up_command(const uschar ***argvptr, uschar *cmd,
  BOOL expand_arguments, int expand_failed, address_item *addr,
  uschar *etext, uschar **errptr)
{
address_item *ad;
const uschar **argv;
uschar *s, *ss;
int address_count = 0;
int argcount = 0;
int i, max_args;


for (ad = addr; ad != NULL; ad = ad->next) address_count++;
max_args = address_count + 60;
*argvptr = argv = store_get((max_args+1)*sizeof(uschar *));


s = cmd;
while (isspace(*s)) s++;

while (*s != 0 && argcount < max_args)
  {
  if (*s == '\'')
    {
    ss = s + 1;
    while (*ss != 0 && *ss != '\'') ss++;
    argv[argcount++] = ss = store_get(ss - s++);
    while (*s != 0 && *s != '\'') *ss++ = *s++;
    if (*s != 0) s++;
    *ss++ = 0;
    }
  else argv[argcount++] = string_copy(string_dequote(CUSS &s));
  while (isspace(*s)) s++;
  }

argv[argcount] = US 0;


if (*s != 0)
  {
  uschar *msg = string_sprintf("Too many arguments in command \"%s\" in "
    "%s", cmd, etext);
  if (addr != NULL)
    {
    addr->transport_return = FAIL;
    addr->message = msg;
    }
  else *errptr = msg;
  return FALSE;
  }


DEBUG(D_transport)
  {
  debug_printf("direct command:\n");
  for (i = 0; argv[i] != US 0; i++)
    debug_printf("  argv[%d] = %s\n", i, string_printing(argv[i]));
  }

if (expand_arguments)
  {
  BOOL allow_dollar_recipients = addr != NULL &&
    addr->parent != NULL &&
    Ustrcmp(addr->parent->address, "system-filter") == 0;

  for (i = 0; argv[i] != US 0; i++)
    {


    if (addr != NULL &&
        (Ustrcmp(argv[i], "$pipe_addresses") == 0 ||
         Ustrcmp(argv[i], "${pipe_addresses}") == 0))
      {
      int additional;

      if (argcount + address_count - 1 > max_args)
        {
        addr->transport_return = FAIL;
        addr->message = string_sprintf("Too many arguments to command \"%s\" "
          "in %s", cmd, etext);
        return FALSE;
        }

      additional = address_count - 1;
      if (additional > 0)
        memmove(argv + i + 1 + additional, argv + i + 1,
          (argcount - i)*sizeof(uschar *));

      for (ad = addr; ad != NULL; ad = ad->next) {
          argv[i++] = ad->address;
          argcount++;
      }


      argcount--;
      i--;
      }


    else if (addr != NULL && testflag(addr,af_force_command) &&
        (Ustrcmp(argv[i], "$address_pipe") == 0 ||
         Ustrcmp(argv[i], "${address_pipe}") == 0))
      {
      int address_pipe_i;
      int address_pipe_argcount = 0;
      int address_pipe_max_args;
      uschar **address_pipe_argv;


      address_pipe_max_args = max_args - argcount + 1;

      DEBUG(D_transport)
        debug_printf("address_pipe_max_args=%d\n", address_pipe_max_args);


      address_pipe_argv = store_get((address_pipe_max_args+1)*sizeof(uschar *));


      s = expand_string(addr->local_part + 1);

      if (s == NULL || *s == '\0')
        {
        addr->transport_return = FAIL;
        addr->message = string_sprintf("Expansion of \"%s\" "
           "from command \"%s\" in %s failed: %s",
           (addr->local_part + 1), cmd, etext, expand_string_message);
        return FALSE;
        }

      while (isspace(*s)) s++;

      while (*s != 0 && address_pipe_argcount < address_pipe_max_args)
        {
        if (*s == '\'')
          {
          ss = s + 1;
          while (*ss != 0 && *ss != '\'') ss++;
          address_pipe_argv[address_pipe_argcount++] = ss = store_get(ss - s++);
          while (*s != 0 && *s != '\'') *ss++ = *s++;
          if (*s != 0) s++;
          *ss++ = 0;
          }
        else address_pipe_argv[address_pipe_argcount++] =
	      string_copy(string_dequote(CUSS &s));
        while (isspace(*s)) s++;
        }

      address_pipe_argv[address_pipe_argcount] = US 0;


      if (*s != 0)
        {
        uschar *msg = string_sprintf("Too many arguments in $address_pipe "
          "\"%s\" in %s", addr->local_part + 1, etext);
        if (addr != NULL)
          {
          addr->transport_return = FAIL;
          addr->message = msg;
          }
        else *errptr = msg;
        return FALSE;
        }


      if (argcount + address_pipe_argcount - 1 > max_args)
        {
        addr->transport_return = FAIL;
        addr->message = string_sprintf("Too many arguments to command "
          "\"%s\" after expanding $address_pipe in %s", cmd, etext);
        return FALSE;
        }


      if (address_pipe_argcount > 1)
        memmove(

          argv + i + address_pipe_argcount,

          argv + i + 1,

          (argcount - i)*sizeof(uschar *)
        );


      for (address_pipe_i = 0;
           address_pipe_argv[address_pipe_i] != US 0;
           address_pipe_i++)
        {
        argv[i++] = address_pipe_argv[address_pipe_i];
        argcount++;
        }


      argcount--;
      i--;
      }


    else
      {
      const uschar *expanded_arg;
      f.enable_dollar_recipients = allow_dollar_recipients;
      expanded_arg = expand_cstring(argv[i]);
      f.enable_dollar_recipients = FALSE;

      if (expanded_arg == NULL)
        {
        uschar *msg = string_sprintf("Expansion of \"%s\" "
          "from command \"%s\" in %s failed: %s",
          argv[i], cmd, etext, expand_string_message);
        if (addr != NULL)
          {
          addr->transport_return = expand_failed;
          addr->message = msg;
          }
        else *errptr = msg;
        return FALSE;
        }
      argv[i] = expanded_arg;
      }
    }

  DEBUG(D_transport)
    {
    debug_printf("direct command after expansion:\n");
    for (i = 0; argv[i] != US 0; i++)
      debug_printf("  argv[%d] = %s\n", i, string_printing(argv[i]));
    }
  }

return TRUE;
}
