failure_log(address_item * addr, uschar * driver_kind, uschar * now)
{
void * reset_point;
gstring * g = reset_point = string_get(256);

#ifndef DISABLE_EVENT


if (  !addr->prop.ignore_error
   && !(addr->dsn_flags & (rf_dsnflags & ~rf_notify_failure))
   )
  msg_event_raise(US"msg:fail:delivery", addr);
#endif


g = string_log_address(g, addr, LOGGING(all_parents), FALSE);

if (LOGGING(sender_on_delivery))
  g = string_append(g, 3, US" F=<", sender_address, US">");

if (*queue_name)
  g = string_append(g, 2, US" Q=", queue_name);


if (used_return_path && LOGGING(return_path_on_delivery))
  g = string_append(g, 3, US" P=<", used_return_path, US">");

if (addr->router)
  g = string_append(g, 2, US" R=", addr->router->name);
if (addr->transport)
  g = string_append(g, 2, US" T=", addr->transport->name);

if (addr->host_used)
  g = d_hostlog(g, addr);

#ifdef SUPPORT_TLS
g = d_tlslog(g, addr);
#endif

if (addr->basic_errno > 0)
  g = string_append(g, 2, US": ", US strerror(addr->basic_errno));

if (addr->message)
  g = string_append(g, 2, US": ", addr->message);

(void) string_from_gstring(g);


if (driver_kind)
  deliver_msglog("%s %s failed for %s\n", now, driver_kind, g->s);
else
  deliver_msglog("%s %s\n", now, g->s);

log_write(0, LOG_MAIN, "** %s", g->s);

store_reset(reset_point);
return;
}
