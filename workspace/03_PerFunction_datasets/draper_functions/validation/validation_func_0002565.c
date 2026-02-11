git_buf_putcn(git_buf *buf, char c, size_t len)
{
	ENSURE_SIZE(buf, buf->size + len + 1);
	memset(buf->ptr + buf->size, c, len);
	buf->size += len;
	buf->ptr[buf->size] = '\0';
	return 0;
}
