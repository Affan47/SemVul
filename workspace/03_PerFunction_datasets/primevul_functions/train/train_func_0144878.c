cgi_set_sid(void)
{
  char			buffer[512],
			sid[33];
  unsigned char		sum[16];
  const char		*remote_addr,
			*server_name,
			*server_port;
  struct timeval	curtime;


  if ((remote_addr = getenv("REMOTE_ADDR")) == NULL)
    remote_addr = "REMOTE_ADDR";
  if ((server_name = getenv("SERVER_NAME")) == NULL)
    server_name = "SERVER_NAME";
  if ((server_port = getenv("SERVER_PORT")) == NULL)
    server_port = "SERVER_PORT";

  gettimeofday(&curtime, NULL);
  CUPS_SRAND(curtime.tv_sec + curtime.tv_usec);
  snprintf(buffer, sizeof(buffer), "%s:%s:%s:%02X%02X%02X%02X%02X%02X%02X%02X",
           remote_addr, server_name, server_port,
	   (unsigned)CUPS_RAND() & 255, (unsigned)CUPS_RAND() & 255,
	   (unsigned)CUPS_RAND() & 255, (unsigned)CUPS_RAND() & 255,
	   (unsigned)CUPS_RAND() & 255, (unsigned)CUPS_RAND() & 255,
	   (unsigned)CUPS_RAND() & 255, (unsigned)CUPS_RAND() & 255);
  cupsHashData("md5", (unsigned char *)buffer, strlen(buffer), sum, sizeof(sum));

  cgiSetCookie(CUPS_SID, cupsHashString(sum, sizeof(sum), sid, sizeof(sid)), "/", NULL, 0, 0);

  return (cupsGetOption(CUPS_SID, num_cookies, cookies));
}
