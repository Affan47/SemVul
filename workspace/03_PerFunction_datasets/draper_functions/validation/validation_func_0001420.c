gf_sdp_fmtp_del(GF_SDP_FMTP *fmtp)
{
	GF_X_Attribute *att;
	if (!fmtp) return;
	while (gf_list_count(fmtp->Attributes)) {
		att = (GF_X_Attribute*)gf_list_get(fmtp->Attributes, 0);
		gf_list_rem(fmtp->Attributes, 0);
		if (att->Name) gf_free(att->Name);
		if (att->Value) gf_free(att->Value);
		gf_free(att);
	}
	gf_list_del(fmtp->Attributes);
	gf_free(fmtp);
}
