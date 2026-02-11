zxid_saml2_redir_url(zxid_conf* cf, struct zx_str* loc, struct zx_str* pay_load, char* relay_state)
{
  struct zx_str* ss;
  struct zx_str* rse = zxid_saml2_redir_enc(cf, "SAMLRequest=", pay_load, relay_state);
  if (!loc || !rse) {
    ERR("Redirection location URL missing. rse(%.*s) %p", rse?rse->len:0, rse?STRNULLCHK(rse->s):"", rse);
    return 0;
  }
  ss = zx_strf(cf->ctx, (memchr(loc->s, '?', loc->len)
			 ? "%.*s&%.*s" CRLF2
			 : "%.*s?%.*s" CRLF2), loc->len, loc->s, rse->len, rse->s);
  D("%.*s", ss->len, ss->s);
  if (zx_debug & ZXID_INOUT) INFO("%.*s", ss->len, ss->s);
  zx_str_free(cf->ctx, rse);
  return ss;
}
