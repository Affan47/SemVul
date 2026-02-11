buf_destroy (buf)
     struct Buf *buf;
{
	if (buf && buf->elts)
		flex_free (buf->elts);
	buf->elts = (void *) 0;
}
