load_lan_channel_numbers (bmc_config_state_data_t *state_data)
{
  int ret;

  assert (state_data);

  if ((ret = ipmi_get_channel_numbers (state_data->ipmi_ctx,
                                       IPMI_CHANNEL_MEDIUM_TYPE_LAN_802_3,
                                       state_data->lan_channel_numbers,
                                       CHANNEL_NUMBERS_MAX)) < 0)
    {
      if (state_data->prog_data->args->config_args.common.debug)
        pstdout_fprintf (state_data->pstate,
                         stderr,
                         "ipmi_get_channel_numbers: %s\n",
                         ipmi_ctx_errormsg (state_data->ipmi_ctx));
      return (CONFIG_ERR_NON_FATAL_ERROR);
    }

  state_data->lan_channel_numbers_count = (unsigned int)ret;
  state_data->lan_channel_numbers_loaded++;

  return (CONFIG_ERR_SUCCESS);
}
