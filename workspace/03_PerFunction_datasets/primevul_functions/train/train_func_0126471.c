setup_proxy_protocol_host()
{
union {
  struct {
    uschar line[108];
  } v1;
  struct {
    uschar sig[12];
    uint8_t ver_cmd;
    uint8_t fam;
    uint16_t len;
    union {
      struct {
        uint32_t src_addr;
        uint32_t dst_addr;
        uint16_t src_port;
        uint16_t dst_port;
      } ip4;
      struct {
        uint8_t  src_addr[16];
        uint8_t  dst_addr[16];
        uint16_t src_port;
        uint16_t dst_port;
      } ip6;
      struct {
        uschar   src_addr[108];
        uschar   dst_addr[108];
      } unx;
    } addr;
  } v2;
} hdr;


uint16_t tmpport;
char tmpip[INET_ADDRSTRLEN];
struct sockaddr_in tmpaddr;
char tmpip6[INET6_ADDRSTRLEN];
struct sockaddr_in6 tmpaddr6;


#define PROXY_INITIAL_READ 14
#define PROXY_V2_HEADER_SIZE 16
#if PROXY_INITIAL_READ > PROXY_V2_HEADER_SIZE
# error Code bug in sizes of data to read for proxy usage
#endif

int get_ok = 0;
int size, ret;
int fd = fileno(smtp_in);
const char v2sig[12] = "\x0D\x0A\x0D\x0A\x00\x0D\x0A\x51\x55\x49\x54\x0A";
uschar * iptype;
struct timeval tv;
struct timeval tvtmp;
socklen_t vslen = sizeof(struct timeval);
BOOL yield = FALSE;


get_ok = getsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, CS &tvtmp, &vslen);


tv.tv_sec  = PROXY_NEGOTIATION_TIMEOUT_SEC;
tv.tv_usec = PROXY_NEGOTIATION_TIMEOUT_USEC;
if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, CS &tv, sizeof(tv)) < 0)
  goto bad;

do
  {


  ret = recv(fd, &hdr, PROXY_INITIAL_READ, 0);
  }
  while (ret == -1 && errno == EINTR);

if (ret == -1)
  goto proxyfail;


if ((ret == PROXY_INITIAL_READ) && (memcmp(&hdr.v2, v2sig, sizeof(v2sig)) == 0))
  {
  int retmore;
  uint8_t ver;


  do
    {
    retmore = recv(fd, (uschar*)&hdr + ret, PROXY_V2_HEADER_SIZE - PROXY_INITIAL_READ, 0);
    } while (retmore == -1 && errno == EINTR);
  if (retmore == -1)
    goto proxyfail;
  ret += retmore;

  ver = (hdr.v2.ver_cmd & 0xf0) >> 4;


  if (ver != 0x02)
    {
    DEBUG(D_receive) debug_printf("Invalid Proxy Protocol version: %d\n", ver);
    goto proxyfail;
    }


  size = 16 + ntohs(hdr.v2.len);
  DEBUG(D_receive) debug_printf("Detected PROXYv2 header, size %d (limit %d)\n",
      size, (int)sizeof(hdr));


  if (size > sizeof(hdr))
    {
    DEBUG(D_receive) debug_printf("PROXYv2 header size unreasonably large; security attack?\n");
    goto proxyfail;
    }

  do
    {
    do
      {
      retmore = recv(fd, (uschar*)&hdr + ret, size-ret, 0);
      } while (retmore == -1 && errno == EINTR);
    if (retmore == -1)
      goto proxyfail;
    ret += retmore;
    DEBUG(D_receive) debug_printf("PROXYv2: have %d/%d required octets\n", ret, size);
    } while (ret < size);

  }


if (ret >= 16 && memcmp(&hdr.v2, v2sig, 12) == 0)
  {
  uint8_t cmd = (hdr.v2.ver_cmd & 0x0f);

  switch (cmd)
    {
    case 0x01:
      switch (hdr.v2.fam)
        {
        case 0x11:
          iptype = US"IPv4";
          tmpaddr.sin_addr.s_addr = hdr.v2.addr.ip4.src_addr;
          inet_ntop(AF_INET, &tmpaddr.sin_addr, CS &tmpip, sizeof(tmpip));
          if (!string_is_ip_address(US tmpip, NULL))
            {
            DEBUG(D_receive) debug_printf("Invalid %s source IP\n", iptype);
            goto proxyfail;
            }
          proxy_local_address = sender_host_address;
          sender_host_address = string_copy(US tmpip);
          tmpport             = ntohs(hdr.v2.addr.ip4.src_port);
          proxy_local_port    = sender_host_port;
          sender_host_port    = tmpport;

          tmpaddr.sin_addr.s_addr = hdr.v2.addr.ip4.dst_addr;
          inet_ntop(AF_INET, &tmpaddr.sin_addr, CS &tmpip, sizeof(tmpip));
          if (!string_is_ip_address(US tmpip, NULL))
            {
            DEBUG(D_receive) debug_printf("Invalid %s dest port\n", iptype);
            goto proxyfail;
            }
          proxy_external_address = string_copy(US tmpip);
          tmpport              = ntohs(hdr.v2.addr.ip4.dst_port);
          proxy_external_port  = tmpport;
          goto done;
        case 0x21:
          iptype = US"IPv6";
          memmove(tmpaddr6.sin6_addr.s6_addr, hdr.v2.addr.ip6.src_addr, 16);
          inet_ntop(AF_INET6, &tmpaddr6.sin6_addr, CS &tmpip6, sizeof(tmpip6));
          if (!string_is_ip_address(US tmpip6, NULL))
            {
            DEBUG(D_receive) debug_printf("Invalid %s source IP\n", iptype);
            goto proxyfail;
            }
          proxy_local_address = sender_host_address;
          sender_host_address = string_copy(US tmpip6);
          tmpport             = ntohs(hdr.v2.addr.ip6.src_port);
          proxy_local_port    = sender_host_port;
          sender_host_port    = tmpport;

          memmove(tmpaddr6.sin6_addr.s6_addr, hdr.v2.addr.ip6.dst_addr, 16);
          inet_ntop(AF_INET6, &tmpaddr6.sin6_addr, CS &tmpip6, sizeof(tmpip6));
          if (!string_is_ip_address(US tmpip6, NULL))
            {
            DEBUG(D_receive) debug_printf("Invalid %s dest port\n", iptype);
            goto proxyfail;
            }
          proxy_external_address = string_copy(US tmpip6);
          tmpport              = ntohs(hdr.v2.addr.ip6.dst_port);
          proxy_external_port  = tmpport;
          goto done;
        default:
          DEBUG(D_receive)
            debug_printf("Unsupported PROXYv2 connection type: 0x%02x\n",
                         hdr.v2.fam);
          goto proxyfail;
        }

      break;
    case 0x00:

      iptype = US"local";
      break;
    default:
      DEBUG(D_receive)
        debug_printf("Unsupported PROXYv2 command: 0x%x\n", cmd);
      goto proxyfail;
    }
  }
else if (ret >= 8 && memcmp(hdr.v1.line, "PROXY", 5) == 0)
  {
  uschar *p;
  uschar *end;
  uschar *sp;
  int     tmp_port;
  int     r2;
  char   *endc;


  r2 = swallow_until_crlf(fd, (uschar*)&hdr, ret, sizeof(hdr)-ret);
  if (r2 == -1)
    goto proxyfail;
  ret += r2;

  p = string_copy(hdr.v1.line);
  end = memchr(p, '\r', ret - 1);

  if (!end || (end == (uschar*)&hdr + ret) || end[1] != '\n')
    {
    DEBUG(D_receive) debug_printf("Partial or invalid PROXY header\n");
    goto proxyfail;
    }
  *end = '\0';
  size = end + 2 - p;
  DEBUG(D_receive) debug_printf("Detected PROXYv1 header\n");
  DEBUG(D_receive) debug_printf("Bytes read not within PROXY header: %d\n", ret - size);


  p += 5;
  if (!isspace(*(p++)))
    {
    DEBUG(D_receive) debug_printf("Missing space after PROXY command\n");
    goto proxyfail;
    }
  if (!Ustrncmp(p, CCS"TCP4", 4))
    iptype = US"IPv4";
  else if (!Ustrncmp(p,CCS"TCP6", 4))
    iptype = US"IPv6";
  else if (!Ustrncmp(p,CCS"UNKNOWN", 7))
    {
    iptype = US"Unknown";
    goto done;
    }
  else
    {
    DEBUG(D_receive) debug_printf("Invalid TCP type\n");
    goto proxyfail;
    }

  p += Ustrlen(iptype);
  if (!isspace(*(p++)))
    {
    DEBUG(D_receive) debug_printf("Missing space after TCP4/6 command\n");
    goto proxyfail;
    }

  if ((sp = Ustrchr(p, ' ')) == NULL)
    {
    DEBUG(D_receive)
      debug_printf("Did not find proxied src %s\n", iptype);
    goto proxyfail;
    }
  *sp = '\0';
  if(!string_is_ip_address(p, NULL))
    {
    DEBUG(D_receive)
      debug_printf("Proxied src arg is not an %s address\n", iptype);
    goto proxyfail;
    }
  proxy_local_address = sender_host_address;
  sender_host_address = p;
  p = sp + 1;
  if ((sp = Ustrchr(p, ' ')) == NULL)
    {
    DEBUG(D_receive)
      debug_printf("Did not find proxy dest %s\n", iptype);
    goto proxyfail;
    }
  *sp = '\0';
  if(!string_is_ip_address(p, NULL))
    {
    DEBUG(D_receive)
      debug_printf("Proxy dest arg is not an %s address\n", iptype);
    goto proxyfail;
    }
  proxy_external_address = p;
  p = sp + 1;
  if ((sp = Ustrchr(p, ' ')) == NULL)
    {
    DEBUG(D_receive) debug_printf("Did not find proxied src port\n");
    goto proxyfail;
    }
  *sp = '\0';
  tmp_port = strtol(CCS p, &endc, 10);
  if (*endc || tmp_port == 0)
    {
    DEBUG(D_receive)
      debug_printf("Proxied src port '%s' not an integer\n", p);
    goto proxyfail;
    }
  proxy_local_port = sender_host_port;
  sender_host_port = tmp_port;
  p = sp + 1;
  if ((sp = Ustrchr(p, '\0')) == NULL)
    {
    DEBUG(D_receive) debug_printf("Did not find proxy dest port\n");
    goto proxyfail;
    }
  tmp_port = strtol(CCS p, &endc, 10);
  if (*endc || tmp_port == 0)
    {
    DEBUG(D_receive)
      debug_printf("Proxy dest port '%s' not an integer\n", p);
    goto proxyfail;
    }
  proxy_external_port = tmp_port;

  }
else
  {

  DEBUG(D_receive) debug_printf("Invalid proxy protocol version negotiation\n");
  (void) swallow_until_crlf(fd, (uschar*)&hdr, ret, sizeof(hdr)-ret);
  goto proxyfail;
  }

done:
  DEBUG(D_receive)
    debug_printf("Valid %s sender from Proxy Protocol header\n", iptype);
  yield = proxy_session;


proxyfail:
  restore_socket_timeout(fd, get_ok, &tvtmp, vslen);

bad:
  if (yield)
    {
    sender_host_name = NULL;
    (void) host_name_lookup();
    host_build_sender_fullhost();
    }
  else
    {
    f.proxy_session_failed = TRUE;
    DEBUG(D_receive)
      debug_printf("Failure to extract proxied host, only QUIT allowed\n");
    }

return;
}
