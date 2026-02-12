readconf_driver_init(
  uschar *class,
  driver_instance **anchor,
  driver_info *drivers_available,
  int size_of_info,
  void *instance_default,
  int  instance_size,
  optionlist *driver_optionlist,
  int  driver_optionlist_count)
{
driver_instance **p = anchor;
driver_instance *d = NULL;
uschar *buffer;

while ((buffer = get_config_line()) != NULL)
  {
  uschar name[64];
  uschar *s;


  s = readconf_readname(name, sizeof(name), buffer);


  if (isupper(*name) && *s == '=')
    {
    if (d != NULL)
      {
      if (d->driver_name == NULL)
        log_write(0, LOG_PANIC_DIE|LOG_CONFIG,
          "no driver defined for %s \"%s\"", class, d->name);
      (d->info->init)(d);
      d = NULL;
      }
    read_macro_assignment(buffer);
    continue;
    }


  if (*s++ == ':')
    {
    int i;


    if (d != NULL)
      {
      if (d->driver_name == NULL)
        log_write(0, LOG_PANIC_DIE|LOG_CONFIG,
          "no driver defined for %s \"%s\"", class, d->name);
      (d->info->init)(d);
      }


    for (d = *anchor; d != NULL; d = d->next)
      if (Ustrcmp(name, d->name) == 0)
        log_write(0, LOG_PANIC_DIE|LOG_CONFIG,
          "there are two %ss called \"%s\"", class, name);


    d = store_get(instance_size);
    memcpy(d, instance_default, instance_size);
    *p = d;
    p = &(d->next);
    d->name = string_copy(name);


    for (i = 0; i < driver_optionlist_count; i++)
      driver_optionlist[i].type &= ~opt_set;


    while (isspace(*s)) s++;
    if (*s != 0) extra_chars_error(s, US"driver name ", name, US"");
    continue;
    }


  if (d == NULL) log_write(0, LOG_PANIC_DIE|LOG_CONFIG_IN,
    "%s name missing", class);


  if (readconf_handle_option(buffer, driver_optionlist,
        driver_optionlist_count, d, NULL))
    {
    if (d->info == NULL && d->driver_name != NULL)
      init_driver(d, drivers_available, size_of_info, class);
    }


  else if (d->info != NULL)
    {
    readconf_handle_option(buffer, d->info->options,
      *(d->info->options_count), d, US"option \"%s\" unknown");
    }


  else log_write(0, LOG_PANIC_DIE|LOG_CONFIG_IN, "option \"%s\" unknown "
    "(\"driver\" must be specified before any private options)", name);
  }


if (d != NULL)
  {
  if (d->driver_name == NULL)
    log_write(0, LOG_PANIC_DIE|LOG_CONFIG,
      "no driver defined for %s \"%s\"", class, d->name);
  (d->info->init)(d);
  }
}
