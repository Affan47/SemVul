network_reentry_is_allowed(void)
{

  return !!networkstatus_get_param(NULL, "allow-network-reentry", 0, 0, 1);
}
