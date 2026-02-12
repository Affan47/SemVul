static size_t upcall_msg_size(const struct nlattr *userdata,
			      unsigned int hdrlen)
{
	size_t size = NLMSG_ALIGN(sizeof(struct ovs_header))
		+ nla_total_size(hdrlen)
		+ nla_total_size(key_attr_size());


	if (userdata)
		size += NLA_ALIGN(userdata->nla_len);

	return size;
}
