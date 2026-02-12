get_config_line(void)
{
int startoffset = 0;
int len = 0;
int newlen;
uschar *s, *ss;
macro_item *m;
BOOL macro_found;


for (;;)
  {
  if (Ufgets(big_buffer+len, big_buffer_size-len, config_file) == NULL)
    {
    if (config_file_stack != NULL)
      {
      (void)fclose(config_file);
      config_file = config_file_stack->file;
      config_filename = config_file_stack->filename;
      config_lineno = config_file_stack->lineno;
      config_file_stack = config_file_stack->next;
      continue;
      }


    if (cstate_stack_ptr >= 0)
      log_write(0, LOG_PANIC_DIE|LOG_CONFIG_IN,
        "Unexpected end of configuration file: .endif missing");

    if (len != 0) break;
    next_section[0] = 0;
    return NULL;
    }

  config_lineno++;
  newlen = len + Ustrlen(big_buffer + len);


  while (newlen == big_buffer_size - 1 && big_buffer[newlen - 1] != '\n')
    {
    uschar *newbuffer;
    big_buffer_size += BIG_BUFFER_SIZE;
    newbuffer = store_malloc(big_buffer_size);


    Ustrcpy(newbuffer, big_buffer);
    store_free(big_buffer);
    big_buffer = newbuffer;
    if (Ufgets(big_buffer+newlen, big_buffer_size-newlen, config_file) == NULL)
      break;
    newlen += Ustrlen(big_buffer + newlen);
    }


  ss = big_buffer + len;
  while (isspace(*ss)) ss++;


  s = ss;
  if (len == 0 && isupper(*s))
    {
    while (isalnum(*s) || *s == '_') s++;
    while (isspace(*s)) s++;
    if (*s != '=') s = ss;
    }


  macro_found = FALSE;
  for (m = macros; m != NULL; m = m->next)
    {
    uschar *p, *pp;
    uschar *t = s;

    while ((p = Ustrstr(t, m->name)) != NULL)
      {
      int moveby;
      int namelen = Ustrlen(m->name);
      int replen = Ustrlen(m->replacement);


      while (newlen - namelen + replen + 1 > big_buffer_size)
        {
        int newsize = big_buffer_size + BIG_BUFFER_SIZE;
        uschar *newbuffer = store_malloc(newsize);
        memcpy(newbuffer, big_buffer, newlen + 1);
        p = newbuffer  + (p - big_buffer);
        s = newbuffer  + (s - big_buffer);
        ss = newbuffer + (ss - big_buffer);
        t = newbuffer  + (t - big_buffer);
        big_buffer_size = newsize;
        store_free(big_buffer);
        big_buffer = newbuffer;
        }


      pp = p + namelen;
      moveby = replen - namelen;
      if (moveby != 0)
        {
        memmove(p + replen, pp, (big_buffer + newlen) - pp + 1);
        newlen += moveby;
        }
      Ustrncpy(p, m->replacement, replen);
      t = p + replen;
      macro_found = TRUE;
      }
    }


  while (isspace(*ss)) ss++;


  if (*ss == '#') continue;


  if (*ss == '.')
    {
    int i;


    for (i = 0; i < cond_list_size; i++)
      {
      int n;
      cond_item *c = cond_list+i;
      if (Ustrncmp(ss+1, c->name, c->namelen) != 0) continue;


      n = ss[1 + c->namelen];
      if (n != ' ' && n != 't' && n != '\n' && n != 0) break;


      if (c->pushpop > 0)
        {
        if (cstate_stack_ptr >= CSTATE_STACK_SIZE - 1)
          log_write(0, LOG_PANIC_DIE|LOG_CONFIG_IN,
            ".%s nested too deeply", c->name);
        cstate_stack[++cstate_stack_ptr] = cstate;
        cstate = next_cstate[cstate][macro_found? c->action1 : c->action2];
        }


      else
        {
        if (cstate_stack_ptr < 0)
          log_write(0, LOG_PANIC_DIE|LOG_CONFIG_IN,
            ".%s without matching .ifdef", c->name);
        cstate = (c->pushpop < 0)? cstate_stack[cstate_stack_ptr--] :
          next_cstate[cstate][macro_found? c->action1 : c->action2];
        }


      break;
      }


    if (i < cond_list_size) continue;
    }


  if (cstate != 0) continue;


  if (Ustrncmp(ss, ".include", 8) == 0 &&
       (isspace(ss[8]) ||
         (Ustrncmp(ss+8, "_if_exists", 10) == 0 && isspace(ss[18]))))
    {
    uschar *t;
    int include_if_exists = isspace(ss[8])? 0 : 10;
    config_file_item *save;
    struct stat statbuf;

    ss += 9 + include_if_exists;
    while (isspace(*ss)) ss++;
    t = ss + Ustrlen(ss);
    while (t > ss && isspace(t[-1])) t--;
    if (*ss == '\"' && t[-1] == '\"')
      {
      ss++;
      t--;
      }
    *t = 0;

    if (*ss != '/')
      log_write(0, LOG_PANIC_DIE|LOG_CONFIG_IN, ".include specifies a non-"
        "absolute path \"%s\"", ss);

    if (include_if_exists != 0 && (Ustat(ss, &statbuf) != 0)) continue;

    save = store_get(sizeof(config_file_item));
    save->next = config_file_stack;
    config_file_stack = save;
    save->file = config_file;
    save->filename = config_filename;
    save->lineno = config_lineno;

    config_file = Ufopen(ss, "rb");
    if (config_file == NULL)
      log_write(0, LOG_PANIC_DIE|LOG_CONFIG_IN, "failed to open included "
        "configuration file %s", ss);
    config_filename = string_copy(ss);
    config_lineno = 0;
    continue;
    }


  if (len == 0)
    startoffset = ss - big_buffer;
  else
    {
    s = big_buffer + len;
    if (ss > s)
      {
      memmove(s, ss, (newlen - len) -  (ss - s) + 1);
      newlen -= ss - s;
      }
    }


  len = newlen;
  while (len > 0 && isspace(big_buffer[len-1])) len--;
  big_buffer[len] = 0;


  if (len > 0)
    {
    if (big_buffer[len-1] != '\\') break;
    big_buffer[--len] = 0;
    }
  }


s = big_buffer + startoffset;
if (strncmpic(s, US"begin ", 6) == 0)
  {
  s += 6;
  while (isspace(*s)) s++;
  if (big_buffer + len - s > sizeof(next_section) - 2)
    s[sizeof(next_section) - 2] = 0;
  Ustrcpy(next_section, s);
  return NULL;
  }


return s;
}
