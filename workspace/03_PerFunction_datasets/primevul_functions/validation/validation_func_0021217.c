static __be32 *xdr_get_next_encode_buffer(struct xdr_stream *xdr,
		size_t nbytes)
{
	__be32 *p;
	int space_left;
	int frag1bytes, frag2bytes;

	if (nbytes > PAGE_SIZE)
		goto out_overflow;
	if (xdr->buf->len + nbytes > xdr->buf->buflen)
		goto out_overflow;
	frag1bytes = (xdr->end - xdr->p) << 2;
	frag2bytes = nbytes - frag1bytes;
	if (xdr->iov)
		xdr->iov->iov_len += frag1bytes;
	else
		xdr->buf->page_len += frag1bytes;
	xdr->page_ptr++;
	xdr->iov = NULL;


	xdr_set_scratch_buffer(xdr, xdr->p, frag1bytes);
	p = page_address(*xdr->page_ptr);


	xdr->p = (void *)p + frag2bytes;
	space_left = xdr->buf->buflen - xdr->buf->len;
	xdr->end = (void *)p + min_t(int, space_left, PAGE_SIZE);
	xdr->buf->page_len += frag2bytes;
	xdr->buf->len += nbytes;
	return p;
out_overflow:
	trace_rpc_xdr_overflow(xdr, nbytes);
	return NULL;
}
