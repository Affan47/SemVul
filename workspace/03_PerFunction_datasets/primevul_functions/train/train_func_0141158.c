deferral_log(address_item * addr, uschar * now,
  int logflags, uschar * driver_name, uschar * driver_kind)
{
gstring * g;
void * reset_point;


g = reset_point = string_get(256);


g = string_log_address(g, addr, LOGGING(all_parents), FALSE);

if (*queue_name)
  g = string_append(g, 2, US" Q=", queue_name);


if (driver_name)
  {
  if (driver_kind[1] == 't' && addr->router)
    g = string_append(g, 2, US" R=", addr->router->name);
  g = string_cat(g, string_sprintf(" %c=%s", toupper(driver_kind[1]), driver_name));
  }
else if (driver_kind)
  g = string_append(g, 2, US" ", driver_kind);


g = string_cat(g, string_sprintf(" defer (%d)", addr->basic_errno));

if (addr->basic_errno > 0)
  g = string_append(g, 2, US": ",
    US strerror(addr->basic_errno));

if (addr->host_used)
  {
  g = string_append(g, 5,
		    US" H=", addr->host_used->name,
		    US" [",  addr->host_used->address, US"]");
  if (LOGGING(outgoing_port))
    {
    int port = addr->host_used->port;
    g = string_append(g, 2,
	  US":", port == PORT_NONE ? US"25" : string_sprintf("%d", port));
    }
  }

if (addr->message)
  g = string_append(g, 2, US": ", addr->message);

(void) string_from_gstring(g);


if (deliver_firsttime || addr->basic_errno > ERRNO_RETRY_BASE)
  deliver_msglog("%s %s\n", now, g->s);


log_write(addr->basic_errno <= ERRNO_RETRY_BASE ? L_retry_defer : 0, logflags,
  "== %s", g->s);

store_reset(reset_point);
return;
}
