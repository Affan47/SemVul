transport_init(void)
{
transport_instance *t;

readconf_driver_init(US"transport",
  (driver_instance **)(&transports),
  (driver_info *)transports_available,
  sizeof(transport_info),
  &transport_defaults,
  sizeof(transport_instance),
  optionlist_transports,
  optionlist_transports_size);


for (t = transports; t; t = t->next)
  {
  if (!t->info->local && t->shadow)
    log_write(0, LOG_PANIC_DIE|LOG_CONFIG,
      "shadow transport not allowed on non-local transport %s", t->name);

  if (t->body_only && t->headers_only)
    log_write(0, LOG_PANIC_DIE|LOG_CONFIG,
      "%s transport: body_only and headers_only are mutually exclusive",
      t->name);
  }
}
