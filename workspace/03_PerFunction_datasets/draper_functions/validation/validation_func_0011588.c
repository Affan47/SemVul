get_cee_app_pri(int nl_sd, const char *ifname,
			   __u8 req_idtype, __u16 req_id)
{
	struct nlmsghdr *nlh;
	struct dcbmsg *d;
	struct rtattr *rta_parent, *rta_child;
	int rval = 0;
	__u8 idtype;
	__u16 id;

	nlh = start_dcbmsg(RTM_GETDCB, DCB_CMD_GAPP);
	if (!nlh)
		return -EIO;

	add_rta(nlh, DCB_ATTR_IFNAME, (void *)ifname, strlen(ifname) + 1);
	rta_parent = add_rta(nlh, DCB_ATTR_APP, NULL, 0);

	rta_child = add_rta(nlh, DCB_APP_ATTR_IDTYPE,
		(void *)&req_idtype, sizeof(__u8));
	rta_parent->rta_len += NLA_ALIGN(rta_child->rta_len);

	rta_child = add_rta(nlh, DCB_APP_ATTR_ID,
		(void *)&req_id, sizeof(__u16));
	rta_parent->rta_len += NLA_ALIGN(rta_child->rta_len);

	rval = dcbnl_send_msg(nl_sd, nlh);
	free(nlh);
	if (rval)
		return -EIO;

	nlh = dcbnl_get_msg(nl_sd);
	if (!nlh)
		return -EIO;

	d = (struct dcbmsg *)NLMSG_DATA(nlh);
	rta_parent = (struct rtattr *)(((char *)d) +
		NLMSG_ALIGN(sizeof(struct dcbmsg)));

	if (d->cmd != DCB_CMD_GAPP) {
		rval = -EIO;
		goto get_error;
	}
	if (rta_parent->rta_type != DCB_ATTR_APP) {
		rval = -EIO;
		goto get_error;
	}

	rta_child = NLA_DATA(rta_parent);
	rta_parent = NLA_NEXT(rta_parent);

	idtype = *(__u8 *)NLA_DATA(rta_child);
	rta_child = NLA_NEXT(rta_child);
	if (idtype != req_idtype) {
		rval = -EIO;
		goto get_error;
	}

	id = *(__u16 *)NLA_DATA(rta_child);
	rta_child = NLA_NEXT(rta_child);
	if (id != req_id) {
		rval = -EIO;
		goto get_error;
	}

	rval = *(__u8 *)NLA_DATA(rta_child);

get_error:
	free(nlh);
	return rval;
}
