attach_bjnp (SANE_String_Const devname,  SANE_String_Const makemodel,
             SANE_String_Const serial,
             const struct pixma_config_t *const pixma_devices[])
{
  scanner_info_t *si;
  const pixma_config_t *cfg;

  si = (scanner_info_t *) calloc (1, sizeof (*si));
  if (!si)
    return SANE_STATUS_NO_MEM;
  si->devname = strdup (devname);
  if (!si->devname)
    return SANE_STATUS_NO_MEM;
  if ((cfg = lookup_scanner(makemodel, pixma_devices)) == (struct pixma_config_t *)NULL)
    return SANE_STATUS_INVAL;
  si->cfg = cfg;
  sprintf(si->serial, "%s_%s", cfg->model, serial);
  si -> interface = INT_BJNP;
  si->next = first_scanner;
  first_scanner = si;
  nscanners++;
  return SANE_STATUS_GOOD;
}
