static int decode_exchange_id(struct xdr_stream *xdr,
			      struct nfs41_exchange_id_res *res)
{
	__be32 *p;
	uint32_t dummy;
	char *dummy_str;
	int status;
	uint32_t impl_id_count;

	status = decode_op_hdr(xdr, OP_EXCHANGE_ID);
	if (status)
		return status;

	p = xdr_inline_decode(xdr, 8);
	if (unlikely(!p))
		return -EIO;
	xdr_decode_hyper(p, &res->clientid);
	p = xdr_inline_decode(xdr, 12);
	if (unlikely(!p))
		return -EIO;
	res->seqid = be32_to_cpup(p++);
	res->flags = be32_to_cpup(p++);

	res->state_protect.how = be32_to_cpup(p);
	switch (res->state_protect.how) {
	case SP4_NONE:
		break;
	case SP4_MACH_CRED:
		status = decode_op_map(xdr, &res->state_protect.enforce);
		if (status)
			return status;
		status = decode_op_map(xdr, &res->state_protect.allow);
		if (status)
			return status;
		break;
	default:
		WARN_ON_ONCE(1);
		return -EIO;
	}


	p = xdr_inline_decode(xdr, 8);
	if (unlikely(!p))
		return -EIO;
	p = xdr_decode_hyper(p, &res->server_owner->minor_id);


	status = decode_opaque_inline(xdr, &dummy, &dummy_str);
	if (unlikely(status))
		return status;
	memcpy(res->server_owner->major_id, dummy_str, dummy);
	res->server_owner->major_id_sz = dummy;


	status = decode_opaque_inline(xdr, &dummy, &dummy_str);
	if (unlikely(status))
		return status;
	memcpy(res->server_scope->server_scope, dummy_str, dummy);
	res->server_scope->server_scope_sz = dummy;


	p = xdr_inline_decode(xdr, 4);
	if (unlikely(!p))
		return -EIO;
	impl_id_count = be32_to_cpup(p++);

	if (impl_id_count) {

		status = decode_opaque_inline(xdr, &dummy, &dummy_str);
		if (unlikely(status))
			return status;
		memcpy(res->impl_id->domain, dummy_str, dummy);


		status = decode_opaque_inline(xdr, &dummy, &dummy_str);
		if (unlikely(status))
			return status;
		memcpy(res->impl_id->name, dummy_str, dummy);


		p = xdr_inline_decode(xdr, 12);
		if (unlikely(!p))
			return -EIO;
		p = xdr_decode_hyper(p, &res->impl_id->date.seconds);
		res->impl_id->date.nseconds = be32_to_cpup(p);


	}
	return 0;
}
