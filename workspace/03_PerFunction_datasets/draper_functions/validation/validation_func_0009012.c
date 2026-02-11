lookup(struct rfc1035_spf_info *info)
{
	char record[256];
	char c;


	if (++*info->lookup_cnt > 20)
	{
		set_err_msg(info->errmsg_buf, info->errmsg_buf_size,
			    "Maximum of 20 nested SPF queries exceeded.");
		return SPF_UNKNOWN;
	}

	c=rfc1035_spf_gettxt(info->current_domain, record);

	if (c != SPF_PASS)
		return c;

	return rfc1035_spf_compute(record, info);
}
