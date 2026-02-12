void xdr_enter_page(struct xdr_stream *xdr, unsigned int len)
{
	len = xdr_align_pages(xdr, len);


	if (len != 0)
		xdr_set_page_base(xdr, 0, len);
}
