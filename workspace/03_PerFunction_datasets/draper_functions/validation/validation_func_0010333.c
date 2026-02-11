rb_linebuf_putbuf(buf_head_t * bufhead, const char *buffer)
{
	buf_line_t *bufline;
	int len = 0;


#ifndef NDEBUG
	if(bufhead->list.tail)
	{
		bufline = bufhead->list.tail->data;
		lrb_assert(bufline->terminated);
	}
#endif

	bufline = rb_linebuf_new_line(bufhead);

	if(rb_unlikely(buffer != NULL))
		len = rb_strlcpy(bufline->buf, buffer, BUF_DATA_SIZE);

	bufline->terminated = 1;


	if(rb_unlikely(len > 510))
	{
		len = 510;
		bufline->buf[len++] = '\r';
		bufline->buf[len++] = '\n';
	}
	else if(rb_unlikely(len == 0))
	{
		bufline->buf[len++] = '\r';
		bufline->buf[len++] = '\n';
		bufline->buf[len] = '\0';
	}
	else
	{

		while((bufline->buf[len] == '\r') || (bufline->buf[len] == '\n')
		      || (bufline->buf[len] == '\0'))
		{
			len--;
		}

		bufline->buf[++len] = '\r';
		bufline->buf[++len] = '\n';
		bufline->buf[++len] = '\0';
	}

	bufline->len = len;
	bufhead->len += len;


}
