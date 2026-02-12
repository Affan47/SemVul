addr_policy_covers(addr_policy_t *a, addr_policy_t *b)
{


  if (a->maskbits > b->maskbits) {

    return 0;
  }
  if (tor_addr_compare_masked(&a->addr, &b->addr, a->maskbits, CMP_EXACT)) {

    return 0;
  }
  return (a->prt_min <= b->prt_min && a->prt_max >= b->prt_max);
}
