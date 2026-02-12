static struct sctp_cookie_param *sctp_pack_cookie(
					const struct sctp_endpoint *ep,
					const struct sctp_association *asoc,
					const struct sctp_chunk *init_chunk,
					int *cookie_len, const __u8 *raw_addrs,
					int addrs_len)
{
	struct sctp_signed_cookie *cookie;
	struct sctp_cookie_param *retval;
	int headersize, bodysize;


	headersize = sizeof(struct sctp_paramhdr) +
		     (sizeof(struct sctp_signed_cookie) -
		      sizeof(struct sctp_cookie));
	bodysize = sizeof(struct sctp_cookie)
		+ ntohs(init_chunk->chunk_hdr->length) + addrs_len;


	if (bodysize % SCTP_COOKIE_MULTIPLE)
		bodysize += SCTP_COOKIE_MULTIPLE
			- (bodysize % SCTP_COOKIE_MULTIPLE);
	*cookie_len = headersize + bodysize;


	retval = kzalloc(*cookie_len, GFP_ATOMIC);
	if (!retval)
		goto nodata;

	cookie = (struct sctp_signed_cookie *) retval->body;


	retval->p.type = SCTP_PARAM_STATE_COOKIE;
	retval->p.length = htons(*cookie_len);


	cookie->c = asoc->c;

	cookie->c.raw_addr_list_len = addrs_len;


	cookie->c.prsctp_capable = asoc->peer.prsctp_capable;


	cookie->c.adaptation_ind = asoc->peer.adaptation_ind;


	cookie->c.expiration = ktime_add(asoc->cookie_life,
					 ktime_get_real());


	memcpy(&cookie->c.peer_init[0], init_chunk->chunk_hdr,
	       ntohs(init_chunk->chunk_hdr->length));


	memcpy((__u8 *)&cookie->c.peer_init[0] +
	       ntohs(init_chunk->chunk_hdr->length), raw_addrs, addrs_len);

	if (sctp_sk(ep->base.sk)->hmac) {
		SHASH_DESC_ON_STACK(desc, sctp_sk(ep->base.sk)->hmac);
		int err;


		desc->tfm = sctp_sk(ep->base.sk)->hmac;
		desc->flags = 0;

		err = crypto_shash_setkey(desc->tfm, ep->secret_key,
					  sizeof(ep->secret_key)) ?:
		      crypto_shash_digest(desc, (u8 *)&cookie->c, bodysize,
					  cookie->signature);
		shash_desc_zero(desc);
		if (err)
			goto free_cookie;
	}

	return retval;

free_cookie:
	kfree(retval);
nodata:
	*cookie_len = 0;
	return NULL;
}
