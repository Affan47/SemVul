exit_policy_remove_redundancies(smartlist_t *dest)
{
  addr_policy_t *ap, *tmp, *victim;
  int i, j;


  for (i = 0; i < smartlist_len(dest); ++i) {
    ap = smartlist_get(dest, i);
    if (ap->maskbits == 0 && ap->prt_min <= 1 && ap->prt_max >= 65535) {

      while (i+1 < smartlist_len(dest)) {
        victim = smartlist_get(dest, i+1);
        smartlist_del(dest, i+1);
        addr_policy_free(victim);
      }
      break;
    }
  }


  for (i = 0; i < smartlist_len(dest)-1; ++i) {
    ap = smartlist_get(dest, i);
    for (j = i+1; j < smartlist_len(dest); ++j) {
      tmp = smartlist_get(dest, j);
      tor_assert(j > i);
      if (addr_policy_covers(ap, tmp)) {
        char p1[POLICY_BUF_LEN], p2[POLICY_BUF_LEN];
        policy_write_item(p1, sizeof(p1), tmp, 0);
        policy_write_item(p2, sizeof(p2), ap, 0);
        log(LOG_DEBUG, LD_CONFIG, "Removing exit policy %s (%d).  It is made "
            "redundant by %s (%d).", p1, j, p2, i);
        smartlist_del_keeporder(dest, j--);
        addr_policy_free(tmp);
      }
    }
  }


  for (i = 0; i < smartlist_len(dest)-1; ++i) {
    ap = smartlist_get(dest, i);
    for (j = i+1; j < smartlist_len(dest); ++j) {


      tmp = smartlist_get(dest, j);
      if (ap->policy_type != tmp->policy_type) {
        if (addr_policy_intersects(ap, tmp))
          break;
      } else {
        if (addr_policy_covers(tmp, ap)) {
          char p1[POLICY_BUF_LEN], p2[POLICY_BUF_LEN];
          policy_write_item(p1, sizeof(p1), ap, 0);
          policy_write_item(p2, sizeof(p2), tmp, 0);
          log(LOG_DEBUG, LD_CONFIG, "Removing exit policy %s.  It is already "
              "covered by %s.", p1, p2);
          smartlist_del_keeporder(dest, i--);
          addr_policy_free(ap);
          break;
        }
      }
    }
  }
}
