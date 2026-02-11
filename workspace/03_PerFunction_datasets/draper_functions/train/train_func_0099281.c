_bmc_device_config_file_parse (struct bmc_device_arguments *cmd_args)
{
  if (config_file_parse (cmd_args->common.config_file,
                         0,
                         &(cmd_args->common),
                         &(cmd_args->sdr),
                         &(cmd_args->hostrange),
                         CONFIG_FILE_INBAND | CONFIG_FILE_OUTOFBAND | CONFIG_FILE_SDR | CONFIG_FILE_HOSTRANGE,
                         CONFIG_FILE_TOOL_BMC_DEVICE,
                         NULL) < 0)
    {
      fprintf (stderr, "config_file_parse: %s\n", strerror (errno));
      exit (1);
    }
}
