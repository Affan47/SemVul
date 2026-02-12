ctnetlink_change_status(struct nf_conn *ct, const struct nlattr * const cda[])
{
	unsigned long d;
	unsigned int status = ntohl(nla_get_be32(cda[CTA_STATUS]));
	d = ct->status ^ status;

	if (d & (IPS_EXPECTED|IPS_CONFIRMED|IPS_DYING))

		return -EBUSY;

	if (d & IPS_SEEN_REPLY && !(status & IPS_SEEN_REPLY))

		return -EBUSY;

	if (d & IPS_ASSURED && !(status & IPS_ASSURED))

		return -EBUSY;

	__ctnetlink_change_status(ct, status, 0);
	return 0;
}
