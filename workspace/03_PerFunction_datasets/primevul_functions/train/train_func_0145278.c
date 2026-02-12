exit_policy_is_general_exit(smartlist_t *policy)
{
  static const int ports[] = { 80, 443, 6667 };
  int n_allowed = 0;
  int i;
  if (!policy)
    return 0;

  for (i = 0; i < 3; ++i) {
    SMARTLIST_FOREACH(policy, addr_policy_t *, p, {
      if (p->prt_min > ports[i] || p->prt_max < ports[i])
        continue;
      if (p->maskbits > 8)
        continue;
      if (tor_addr_is_loopback(&p->addr))
        continue;

      if (p->policy_type == ADDR_POLICY_ACCEPT) {
        ++n_allowed;
        break;
      }
    });
  }
  return n_allowed >= 2;
}
