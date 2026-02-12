void dkim_exim_acl_setup(uschar *id) {
  pdkim_signature *sig = dkim_signatures;
  dkim_cur_sig = NULL;
  dkim_cur_signer = id;
  if (dkim_disable_verify ||
      !id || !dkim_verify_ctx) return;

  while (sig != NULL) {
    uschar *cmp_val = NULL;
    if (Ustrchr(id,'@') != NULL) cmp_val = (uschar *)sig->identity;
                            else cmp_val = (uschar *)sig->domain;
    if (cmp_val && (strcmpic(cmp_val,id) == 0)) {
      dkim_cur_sig = sig;


      dkim_signing_domain   = (uschar *)sig->domain;
      dkim_signing_selector = (uschar *)sig->selector;
      return;
    }
    sig = sig->next;
  }
}
