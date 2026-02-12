delivery_log(int flags, address_item * addr, int logchar, uschar * msg)
{
gstring * g;
void * reset_point;


#ifndef DISABLE_EVENT

  lookup_dnssec_authenticated = NULL;
#endif

g = reset_point = string_get(256);

if (msg)
  g = string_append(g, 2, host_and_ident(TRUE), US" ");
else
  {
  g->s[0] = logchar; g->ptr = 1;
  g = string_catn(g, US"> ", 2);
  }
g = string_log_address(g, addr, LOGGING(all_parents), TRUE);

if (LOGGING(sender_on_delivery) || msg)
  g = string_append(g, 3, US" F=<",
#ifdef SUPPORT_I18N
    testflag(addr, af_utf8_downcvt)
    ? string_address_utf8_to_alabel(sender_address, NULL)
    :
#endif
      sender_address,
  US">");

if (*queue_name)
  g = string_append(g, 2, US" Q=", queue_name);

#ifdef EXPERIMENTAL_SRS
if(addr->prop.srs_sender)
  g = string_append(g, 3, US" SRS=<", addr->prop.srs_sender, US">");
#endif


if (used_return_path && LOGGING(return_path_on_delivery))
  g = string_append(g, 3, US" P=<", used_return_path, US">");

if (msg)
  g = string_append(g, 2, US" ", msg);


if (addr->router)
  g = string_append(g, 2, US" R=", addr->router->name);

g = string_append(g, 2, US" T=", addr->transport->name);

if (LOGGING(delivery_size))
  g = string_append(g, 2, US" S=",
    string_sprintf("%d", transport_count));


if (addr->transport->info->local)
  {
  if (addr->host_list)
    g = string_append(g, 2, US" H=", addr->host_list->name);
  g = d_log_interface(g);
  if (addr->shadow_message)
    g = string_cat(g, addr->shadow_message);
  }


else
  {
  if (addr->host_used)
    {
    g = d_hostlog(g, addr);
    if (continue_sequence > 1)
      g = string_catn(g, US"*", 1);

#ifndef DISABLE_EVENT
    deliver_host_address = addr->host_used->address;
    deliver_host_port =    addr->host_used->port;
    deliver_host =         addr->host_used->name;


    lookup_dnssec_authenticated = addr->host_used->dnssec==DS_YES ? US"yes"
			      : addr->host_used->dnssec==DS_NO ? US"no"
			      : NULL;
#endif
    }

#ifdef SUPPORT_TLS
  g = d_tlslog(g, addr);
#endif

  if (addr->authenticator)
    {
    g = string_append(g, 2, US" A=", addr->authenticator);
    if (addr->auth_id)
      {
      g = string_append(g, 2, US":", addr->auth_id);
      if (LOGGING(smtp_mailauth) && addr->auth_sndr)
        g = string_append(g, 2, US":", addr->auth_sndr);
      }
    }

  if (LOGGING(pipelining) && testflag(addr, af_pipelining))
    g = string_catn(g, US" L", 2);

#ifndef DISABLE_PRDR
  if (testflag(addr, af_prdr_used))
    g = string_catn(g, US" PRDR", 5);
#endif

  if (testflag(addr, af_chunking_used))
    g = string_catn(g, US" K", 2);
  }


if (  LOGGING(smtp_confirmation)
   && addr->message
   && (addr->host_used || Ustrcmp(addr->transport->driver_name, "lmtp") == 0)
   )
  {
  unsigned i;
  unsigned lim = big_buffer_size < 1024 ? big_buffer_size : 1024;
  uschar *p = big_buffer;
  uschar *ss = addr->message;
  *p++ = '\"';
  for (i = 0; i < lim && ss[i] != 0; i++)
    {
    if (ss[i] == '\"' || ss[i] == '\\') *p++ = '\\';
    *p++ = ss[i];
    }
  *p++ = '\"';
  *p = 0;
  g = string_append(g, 2, US" C=", big_buffer);
  }


if (LOGGING(queue_time))
  g = string_append(g, 2, US" QT=",
    string_timesince(&received_time));

if (LOGGING(deliver_time))
  {
  struct timeval diff = {.tv_sec = addr->more_errno, .tv_usec = addr->delivery_usec};
  g = string_append(g, 2, US" DT=", string_timediff(&diff));
  }


log_write(0, flags, "%s", string_from_gstring(g));

#ifndef DISABLE_EVENT
if (!msg) msg_event_raise(US"msg:delivery", addr);
#endif

store_reset(reset_point);
return;
}
