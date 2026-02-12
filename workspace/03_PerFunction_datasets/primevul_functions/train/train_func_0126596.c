host_aton(const uschar *address, int *bin)
{
int x[4];
int v4offset = 0;


if (Ustrchr(address, ':') != NULL)
  {
  const uschar *p = address;
  const uschar *component[8];
  BOOL ipv4_ends = FALSE;
  int ci = 0;
  int nulloffset = 0;
  int v6count = 8;
  int i;


  if (*p == ':') p++;


  while (*p != 0 && *p != '%')
    {
    int len = Ustrcspn(p, ":%");
    if (len == 0) nulloffset = ci;
    if (ci > 7) log_write(0, LOG_MAIN|LOG_PANIC_DIE,
      "Internal error: invalid IPv6 address \"%s\" passed to host_aton()",
      address);
    component[ci++] = p;
    p += len;
    if (*p == ':') p++;
    }


  if (Ustrchr(component[ci-1], '.') != NULL)
    {
    address = component[--ci];
    ipv4_ends = TRUE;
    v4offset = 3;
    v6count = 6;
    }


  if (ci < v6count)
    {
    int insert_count = v6count - ci;
    for (i = v6count-1; i > nulloffset + insert_count; i--)
      component[i] = component[i - insert_count];
    while (i > nulloffset) component[i--] = US"";
    }


  for (i = 0; i < v6count; i += 2)
    bin[i/2] = (Ustrtol(component[i], NULL, 16) << 16) +
      Ustrtol(component[i+1], NULL, 16);


  if (!ipv4_ends) return 4;
  }


(void)sscanf(CS address, "%d.%d.%d.%d", x, x+1, x+2, x+3);
bin[v4offset] = ((uint)x[0] << 24) + (x[1] << 16) + (x[2] << 8) + x[3];
return v4offset+1;
}
