cheat(char *how)
{
  char *p;

  p = strtok(how, ":");
  if(p == NULL) return;

  if(strcmp(p, "freezew") == 0)
  {
    uint16_t addr;

    p = strtok(NULL, ":");
    if(p == NULL) return;

    if(*p == 'G')
    {
      addr = strtoul(p + 1, NULL, 16);
      if(addr > 239) return;

      addr = header.globals + (addr * 2);
    }
    else
    {
      addr = strtoul(p, NULL, 16);
    }

    p = strtok(NULL, ":");
    if(p == NULL) return;

    freezew_cheat[addr] = 1;
    freezew_val  [addr] = strtoul(p, NULL, 0);
  }
}
