ws_validations()
{
  int ret;
  char* nid;
  struct zx_str* ss;
  zxid_ses sess;
  ZERO(&sess, sizeof(sess));
  if (!cf)
    cf = zxid_new_conf_to_cf(0);

  switch (valid_opt) {
  case 'P':
    ss = zxid_wsc_prepare_call(cf, &sess, 0 , "", buf);
    if (!ss)
      return 1;
    if (verbose)
      printf("WSC_PREPARE_CALL(%.*s)\n", ss->len, ss->s);
    return 0;
  case 'v':
    nid = zxid_wsp_validate(cf, &sess, "", buf);
    if (!nid)
      return 1;
    if (verbose)
      printf("WSP_VALIDATE OK nid(%s)\n", nid);
    return 0;
  case 'd':
    ss = zxid_wsp_decorate(cf, &sess, "", buf);
    if (!ss)
      return 1;
    if (verbose)
      printf("WSP_DECORATE(%.*s)\n", ss->len, ss->s);
    return 0;
  case 'V':
    ret = zxid_wsc_valid_resp(cf, &sess, "", buf);
    if (verbose)
      printf("WSC_VALID_RESP(%d)\n", ret);
    if (ret == 1)
      return 0;
    return 1;
  }
  return 2;
}
