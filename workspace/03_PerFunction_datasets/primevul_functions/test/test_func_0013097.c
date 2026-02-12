struct sctp_association *sctp_unpack_cookie(
					const struct sctp_endpoint *ep,
					const struct sctp_association *asoc,
					struct sctp_chunk *chunk, gfp_t gfp,
					int *error, struct sctp_chunk **errp)
{
	struct sctp_association *retval = NULL;
	int headersize, bodysize, fixed_size;
	struct sctp_signed_cookie *cookie;
	struct sk_buff *skb = chunk->skb;
	struct sctp_cookie *bear_cookie;
	__u8 *digest = ep->digest;
	enum sctp_scope scope;
	unsigned int len;
	ktime_t kt;


	headersize = sizeof(struct sctp_chunkhdr) +
		     (sizeof(struct sctp_signed_cookie) -
		      sizeof(struct sctp_cookie));
	bodysize = ntohs(chunk->chunk_hdr->length) - headersize;
	fixed_size = headersize + sizeof(struct sctp_cookie);


	len = ntohs(chunk->chunk_hdr->length);
	if (len < fixed_size + sizeof(struct sctp_chunkhdr))
		goto malformed;


	if (bodysize % SCTP_COOKIE_MULTIPLE)
		goto malformed;


	cookie = chunk->subh.cookie_hdr;
	bear_cookie = &cookie->c;

	if (!sctp_sk(ep->base.sk)->hmac)
		goto no_hmac;


	{
		struct crypto_shash *tfm = sctp_sk(ep->base.sk)->hmac;
		int err;

		err = crypto_shash_setkey(tfm, ep->secret_key,
					  sizeof(ep->secret_key)) ?:
		      crypto_shash_tfm_digest(tfm, (u8 *)bear_cookie, bodysize,
					      digest);
		if (err) {
			*error = -SCTP_IERROR_NOMEM;
			goto fail;
		}
	}

	if (memcmp(digest, cookie->signature, SCTP_SIGNATURE_SIZE)) {
		*error = -SCTP_IERROR_BAD_SIG;
		goto fail;
	}

no_hmac:


	if (ntohl(chunk->sctp_hdr->vtag) != bear_cookie->my_vtag) {
		*error = -SCTP_IERROR_BAD_TAG;
		goto fail;
	}

	if (chunk->sctp_hdr->source != bear_cookie->peer_addr.v4.sin_port ||
	    ntohs(chunk->sctp_hdr->dest) != bear_cookie->my_port) {
		*error = -SCTP_IERROR_BAD_PORTS;
		goto fail;
	}


	if (sock_flag(ep->base.sk, SOCK_TIMESTAMP))
		kt = skb_get_ktime(skb);
	else
		kt = ktime_get_real();

	if (!asoc && ktime_before(bear_cookie->expiration, kt)) {
		suseconds_t usecs = ktime_to_us(ktime_sub(kt, bear_cookie->expiration));
		__be32 n = htonl(usecs);


		*errp = sctp_make_op_error(asoc, chunk,
					   SCTP_ERROR_STALE_COOKIE, &n,
					   sizeof(n), 0);
		if (*errp)
			*error = -SCTP_IERROR_STALE_COOKIE;
		else
			*error = -SCTP_IERROR_NOMEM;

		goto fail;
	}


	scope = sctp_scope(sctp_source(chunk));
	retval = sctp_association_new(ep, ep->base.sk, scope, gfp);
	if (!retval) {
		*error = -SCTP_IERROR_NOMEM;
		goto fail;
	}


	retval->peer.port = ntohs(chunk->sctp_hdr->source);


	memcpy(&retval->c, bear_cookie, sizeof(*bear_cookie));

	if (sctp_assoc_set_bind_addr_from_cookie(retval, bear_cookie,
						 GFP_ATOMIC) < 0) {
		*error = -SCTP_IERROR_NOMEM;
		goto fail;
	}


	if (list_empty(&retval->base.bind_addr.address_list)) {
		sctp_add_bind_addr(&retval->base.bind_addr, &chunk->dest,
				   sizeof(chunk->dest), SCTP_ADDR_SRC,
				   GFP_ATOMIC);
	}

	retval->next_tsn = retval->c.initial_tsn;
	retval->ctsn_ack_point = retval->next_tsn - 1;
	retval->addip_serial = retval->c.initial_tsn;
	retval->strreset_outseq = retval->c.initial_tsn;
	retval->adv_peer_ack_point = retval->ctsn_ack_point;
	retval->peer.prsctp_capable = retval->c.prsctp_capable;
	retval->peer.adaptation_ind = retval->c.adaptation_ind;


	return retval;

fail:
	if (retval)
		sctp_association_free(retval);

	return NULL;

malformed:


	*error = -SCTP_IERROR_MALFORMED;
	goto fail;
}
