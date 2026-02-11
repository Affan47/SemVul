mroute_helper_del_iroute (struct mroute_helper *mh, const struct iroute *ir)
{
  if (ir->netbits >= 0)
    {
      ASSERT (ir->netbits < MR_HELPER_NET_LEN);
      mroute_helper_lock (mh);
      ++mh->cache_generation;
      --mh->net_len_refcount[ir->netbits];
      ASSERT (mh->net_len_refcount[ir->netbits] >= 0);
      if (!mh->net_len_refcount[ir->netbits])
	mroute_helper_regenerate (mh);
      mroute_helper_unlock (mh);
    }
}
