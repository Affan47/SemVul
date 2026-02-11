set_raw_ink_type(stp_vars_t *v)
{
  const inklist_t *inks = stp_escp2_inklist(v);
  int ninktypes = inks->n_inks;
  int i;
  const char *channel_name = stp_get_string_parameter(v, "RawChannels");
  const channel_count_t *count;
  if (!channel_name)
    return 0;
  count = get_channel_count_by_name(channel_name);
  if (!count)
    return 0;


  for (i = 0; i < ninktypes; i++)
    if (inks->inknames[i].inkset == INKSET_EXTENDED &&
	(inks->inknames[i].channel_count == count->count))
      {
	stp_dprintf(STP_DBG_INK, v, "Changing ink type from %s to %s\n",
		    stp_get_string_parameter(v, "InkType") ?
		    stp_get_string_parameter(v, "InkType") : "NULL",
		    inks->inknames[i].name);
	stp_set_string_parameter(v, "InkType", inks->inknames[i].name);
	stp_set_int_parameter(v, "STPIRawChannels", count->count);
	return 1;
      }
  stp_eprintf
    (v, _("This printer does not support raw printer output at depth %d\n"),
     count->count);
  return 0;
}
