construct_reply_info_base(struct regional* region, uint16_t flags, size_t qd,
	time_t ttl, time_t prettl, time_t expttl, size_t an, size_t ns,
	size_t ar, size_t total, enum sec_status sec)
{
	struct reply_info* rep;

	size_t s = sizeof(struct reply_info) - sizeof(struct rrset_ref) +
		sizeof(struct ub_packed_rrset_key*) * total;
	if(total >= RR_COUNT_MAX) return NULL;
	if(region)
		rep = (struct reply_info*)regional_alloc(region, s);
	else	rep = (struct reply_info*)malloc(s +
			sizeof(struct rrset_ref) * (total));
	if(!rep)
		return NULL;
	rep->flags = flags;
	rep->qdcount = qd;
	rep->ttl = ttl;
	rep->prefetch_ttl = prettl;
	rep->serve_expired_ttl = expttl;
	rep->an_numrrsets = an;
	rep->ns_numrrsets = ns;
	rep->ar_numrrsets = ar;
	rep->rrset_count = total;
	rep->security = sec;
	rep->authoritative = 0;

	if(region)
		rep->rrsets = (struct ub_packed_rrset_key**)&(rep->ref[0]);
	else	rep->rrsets = (struct ub_packed_rrset_key**)&(rep->ref[total]);

	memset( rep->rrsets, 0, sizeof(struct ub_packed_rrset_key*) * total);
	if(!region)
		memset( &rep->ref[0], 0, sizeof(struct rrset_ref) * total);
	return rep;
}
