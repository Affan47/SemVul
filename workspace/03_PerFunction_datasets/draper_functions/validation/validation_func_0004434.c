decode_uint32(struct xdr_stream *xdr, u32 *value)
{
	__be32 *p;

	p = xdr_inline_decode(xdr, 4);
	if (unlikely(p == NULL))
		goto out_overflow;
	*value = be32_to_cpup(p);
	return 0;
out_overflow:
	print_overflow_msg(__func__, xdr);
	return -EIO;
}
