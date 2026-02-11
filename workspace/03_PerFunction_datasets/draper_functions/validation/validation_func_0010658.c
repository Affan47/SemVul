process_acquire(private_kernel_netlink_ipsec_t *this,
							struct nlmsghdr *hdr)
{
	struct xfrm_user_acquire *acquire;
	struct rtattr *rta;
	size_t rtasize;
	traffic_selector_t *src_ts, *dst_ts;
	u_int32_t reqid = 0;
	int proto = 0;

	acquire = NLMSG_DATA(hdr);
	rta = XFRM_RTA(hdr, struct xfrm_user_acquire);
	rtasize = XFRM_PAYLOAD(hdr, struct xfrm_user_acquire);

	DBG2(DBG_KNL, "received a XFRM_MSG_ACQUIRE");

	while (RTA_OK(rta, rtasize))
	{
		DBG2(DBG_KNL, "  %N", xfrm_attr_type_names, rta->rta_type);

		if (rta->rta_type == XFRMA_TMPL)
		{
			struct xfrm_user_tmpl* tmpl;
			tmpl = (struct xfrm_user_tmpl*)RTA_DATA(rta);
			reqid = tmpl->reqid;
			proto = tmpl->id.proto;
		}
		rta = RTA_NEXT(rta, rtasize);
	}
	switch (proto)
	{
		case 0:
		case IPPROTO_ESP:
		case IPPROTO_AH:
			break;
		default:

			return;
	}
	src_ts = selector2ts(&acquire->sel, TRUE);
	dst_ts = selector2ts(&acquire->sel, FALSE);

	hydra->kernel_interface->acquire(hydra->kernel_interface, reqid, src_ts,
									 dst_ts);
}
