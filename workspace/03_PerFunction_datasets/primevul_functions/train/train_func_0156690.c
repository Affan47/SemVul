host_build_sender_fullhost(void)
{
BOOL show_helo = TRUE;
uschar * address, * fullhost, * rcvhost;
rmark reset_point;
int len;

if (!sender_host_address) return;

reset_point = store_mark();


address = string_sprintf("[%s]:%d", sender_host_address, sender_host_port);
if (!LOGGING(incoming_port) || sender_host_port <= 0)
  *(Ustrrchr(address, ':')) = 0;


if (!sender_helo_name) show_helo = FALSE;


else if (sender_helo_name[0] == '[' &&
         sender_helo_name[(len=Ustrlen(sender_helo_name))-1] == ']')
  {
  int offset = 1;
  uschar *helo_ip;

  if (strncmpic(sender_helo_name + 1, US"IPv6:", 5) == 0) offset += 5;
  if (strncmpic(sender_helo_name + 1, US"IPv4:", 5) == 0) offset += 5;

  helo_ip = string_copyn(sender_helo_name + offset, len - offset - 1);

  if (string_is_ip_address(helo_ip, NULL) != 0)
    {
    int x[4], y[4];
    int sizex, sizey;
    uschar ipx[48], ipy[48];

    sizex = host_aton(helo_ip, x);
    sizey = host_aton(sender_host_address, y);

    (void)host_nmtoa(sizex, x, -1, ipx, ':');
    (void)host_nmtoa(sizey, y, -1, ipy, ':');

    if (strcmpic(ipx, ipy) == 0) show_helo = FALSE;
    }
  }


if (!sender_host_name)
  {
  uschar *portptr = Ustrstr(address, "]:");
  gstring * g;
  int adlen;

  adlen = portptr ? (++portptr - address) : Ustrlen(address);
  fullhost = sender_helo_name
    ? string_sprintf("(%s) %s", sender_helo_name, address)
    : address;

  g = string_catn(NULL, address, adlen);

  if (sender_ident || show_helo || portptr)
    {
    int firstptr;
    g = string_catn(g, US" (", 2);
    firstptr = g->ptr;

    if (portptr)
      g = string_append(g, 2, US"port=", portptr + 1);

    if (show_helo)
      g = string_append(g, 2,
        firstptr == g->ptr ? US"helo=" : US" helo=", sender_helo_name);

    if (sender_ident)
      g = string_append(g, 2,
        firstptr == g->ptr ? US"ident=" : US" ident=", sender_ident);

    g = string_catn(g, US")", 1);
    }

  rcvhost = string_from_gstring(g);
  }


else
  {
  if (show_helo && strcmpic(sender_host_name, sender_helo_name) == 0)
    show_helo = FALSE;

  if (show_helo)
    {
    fullhost = string_sprintf("%s (%s) %s", sender_host_name,
      sender_helo_name, address);
    rcvhost = sender_ident
      ?  string_sprintf("%s\n\t(%s helo=%s ident=%s)", sender_host_name,
        address, sender_helo_name, sender_ident)
      : string_sprintf("%s (%s helo=%s)", sender_host_name,
        address, sender_helo_name);
    }
  else
    {
    fullhost = string_sprintf("%s %s", sender_host_name, address);
    rcvhost = sender_ident
      ?  string_sprintf("%s (%s ident=%s)", sender_host_name, address,
        sender_ident)
      : string_sprintf("%s (%s)", sender_host_name, address);
    }
  }

sender_fullhost = string_copy_perm(fullhost, TRUE);
sender_rcvhost = string_copy_perm(rcvhost, TRUE);

store_reset(reset_point);

DEBUG(D_host_lookup) debug_printf("sender_fullhost = %s\n", sender_fullhost);
DEBUG(D_host_lookup) debug_printf("sender_rcvhost = %s\n", sender_rcvhost);
}
