zxid_get_epr_address(zxid_conf* cf, zxid_epr* epr) {
  if (!epr)
    return 0;
  return ZX_GET_CONTENT(epr->Address);
}
