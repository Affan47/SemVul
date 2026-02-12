compare_known_tor_addr_to_addr_policy(const tor_addr_t *addr, uint16_t port,
                                      const smartlist_t *policy)
{


  SMARTLIST_FOREACH_BEGIN(policy, addr_policy_t *, tmpe) {

    if (!tor_addr_compare_masked(addr, &tmpe->addr, tmpe->maskbits,
                                 CMP_EXACT)) {
      if (port >= tmpe->prt_min && port <= tmpe->prt_max) {

        return tmpe->policy_type == ADDR_POLICY_ACCEPT ?
          ADDR_POLICY_ACCEPTED : ADDR_POLICY_REJECTED;
      }
    }
  } SMARTLIST_FOREACH_END(tmpe);


  return ADDR_POLICY_ACCEPTED;
}
