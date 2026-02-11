_ipmi_sensors_config_config_args_validate (struct ipmi_sensors_config_arguments *cmd_args)
{
  if ((!cmd_args->config_args.action && !cmd_args->sdr.flush_cache)
      || (cmd_args->config_args.action && cmd_args->sdr.flush_cache)
      || cmd_args->config_args.action == -1)
    {
      fprintf (stderr,
               "Exactly one of --flush-cache, --checkout, --commit, --diff, or --listsections MUST be given\n");
      exit (1);
    }


  if (!cmd_args->config_args.action)
    cmd_args->config_args.action = 1;

  config_args_validate (&(cmd_args->config_args));
}
