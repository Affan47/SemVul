zxid_sp_loc_by_index_raw(zxid_conf* cf, zxid_cgi* cgi,
					zxid_entity* sp_meta, int svc_type,
					struct zx_str* ix, int* binding)
{
  struct zx_str* loc;
  struct zx_md_AssertionConsumerService_s* acs_svc;

  if (!sp_meta || !sp_meta->eid || !sp_meta->ed->SPSSODescriptor) {
    ERR("Entity(%s) does not have SP SSO Descriptor (metadata problem)", sp_meta?STRNULLCHKQ(sp_meta->eid):"-");
    return 0;
  }

  switch (svc_type) {
  case ZXID_ACS_SVC:
    for (acs_svc = sp_meta->ed->SPSSODescriptor->AssertionConsumerService;
	 acs_svc && acs_svc->gg.g.tok == zx_md_AssertionConsumerService_ELEM;
	 acs_svc = (struct zx_md_AssertionConsumerService_s*)acs_svc->gg.g.n)
      if (acs_svc->index && ix->len == acs_svc->index->g.len
	  && !memcmp(ix->s, acs_svc->index->g.s, ix->len)
	  && acs_svc->Location)
	break;
    if (!acs_svc)
      break;
    loc = &acs_svc->Location->g;
    if (!loc)
      break;
    *binding = zxid_protocol_binding_map_saml2(&acs_svc->Binding->g);
    return loc;
  }

  ERR("SP Entity(%s) does not have any %d service with index(%.*s) (metadata problem)", sp_meta->eid, svc_type, ix->len, ix->s);
  *binding = 0;
  return 0;
}
