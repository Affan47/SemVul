brcmf_p2p_request_p2p_if(struct brcmf_p2p_info *p2p,
				    struct brcmf_if *ifp, u8 ea[ETH_ALEN],
				    enum brcmf_fil_p2p_if_types iftype)
{
	struct brcmf_fil_p2p_if_le if_request;
	int err;
	u16 chanspec;


	brcmf_p2p_get_current_chanspec(p2p, &chanspec);


	memcpy(if_request.addr, ea, ETH_ALEN);
	if_request.type = cpu_to_le16((u16)iftype);
	if_request.chspec = cpu_to_le16(chanspec);

	err = brcmf_fil_iovar_data_set(ifp, "p2p_ifadd", &if_request,
				       sizeof(if_request));
	if (err)
		return err;

	return err;
}
