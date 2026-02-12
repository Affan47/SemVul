directory_caches_dir_info(or_options_t *options)
{
  if (options->BridgeRelay || options->DirPort)
    return 1;
  if (!server_mode(options) || !advertised_server_mode())
    return 0;


  return ! router_my_exit_policy_is_reject_star() &&
    should_refuse_unknown_exits(options);
}
