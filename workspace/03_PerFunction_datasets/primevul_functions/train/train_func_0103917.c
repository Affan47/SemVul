ospf_lsa_examin (struct lsa_header * lsah, const u_int16_t lsalen, const u_char headeronly)
{
  unsigned ret;
  struct router_lsa * rlsa;
  if
  (
    lsah->type < OSPF_MAX_LSA &&
    ospf_lsa_minlen[lsah->type] &&
    lsalen < OSPF_LSA_HEADER_SIZE + ospf_lsa_minlen[lsah->type]
  )
  {
    if (IS_DEBUG_OSPF_PACKET (0, RECV))
      zlog_debug ("%s: undersized (%u B) %s",
                  __func__, lsalen, LOOKUP (ospf_lsa_type_msg, lsah->type));
    return MSG_NG;
  }
  switch (lsah->type)
  {
  case OSPF_ROUTER_LSA:

    if (headeronly)
    {
      ret = (lsalen - OSPF_LSA_HEADER_SIZE - OSPF_ROUTER_LSA_MIN_SIZE) % 4 ? MSG_NG : MSG_OK;
      break;
    }
    rlsa = (struct router_lsa *) lsah;
    ret = ospf_router_lsa_links_examin
    (
      (struct router_lsa_link *) rlsa->link,
      lsalen - OSPF_LSA_HEADER_SIZE - 4,
      ntohs (rlsa->links)
    );
    break;
  case OSPF_AS_EXTERNAL_LSA:

  case OSPF_AS_NSSA_LSA:

    ret = (lsalen - OSPF_LSA_HEADER_SIZE - OSPF_AS_EXTERNAL_LSA_MIN_SIZE) % 12 ? MSG_NG : MSG_OK;
    break;


  case OSPF_NETWORK_LSA:

  case OSPF_SUMMARY_LSA:
  case OSPF_ASBR_SUMMARY_LSA:

#ifdef HAVE_OPAQUE_LSA
  case OSPF_OPAQUE_LINK_LSA:
  case OSPF_OPAQUE_AREA_LSA:
  case OSPF_OPAQUE_AS_LSA:


#endif
    ret = lsalen % 4 ? MSG_NG : MSG_OK;
    break;
  default:
    if (IS_DEBUG_OSPF_PACKET (0, RECV))
      zlog_debug ("%s: unsupported LSA type 0x%02x", __func__, lsah->type);
    return MSG_NG;
  }
  if (ret != MSG_OK && IS_DEBUG_OSPF_PACKET (0, RECV))
    zlog_debug ("%s: alignment error in %s",
                __func__, LOOKUP (ospf_lsa_type_msg, lsah->type));
  return ret;
}
