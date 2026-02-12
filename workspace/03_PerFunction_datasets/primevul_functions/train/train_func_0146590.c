static int dccp_setsockopt_cscov(struct sock *sk, int cscov, bool rx)
{
	u8 *list, len;
	int i, rc;

	if (cscov < 0 || cscov > 15)
		return -EINVAL;


	if (cscov == 0)
		return 0;
	len = 16 - cscov;

	list = kmalloc(len, GFP_KERNEL);
	if (list == NULL)
		return -ENOBUFS;

	for (i = 0; i < len; i++)
		list[i] = cscov++;

	rc = dccp_feat_register_sp(sk, DCCPF_MIN_CSUM_COVER, rx, list, len);

	if (rc == 0) {
		if (rx)
			dccp_sk(sk)->dccps_pcrlen = cscov;
		else
			dccp_sk(sk)->dccps_pcslen = cscov;
	}
	kfree(list);
	return rc;
}
