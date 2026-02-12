int http_parse_chunk_size(struct buffer *buf, struct http_msg *msg)
{
	char *ptr = buf->lr;
	char *end = buf->data + buf->size;
	unsigned int chunk = 0;


	while (1) {
		int c;
		if (ptr == buf->r)
			return 0;
		c = hex2i(*ptr);
		if (c < 0)
			break;
		if (++ptr >= end)
			ptr = buf->data;
		if (chunk & 0xF000000)
			goto error;
		chunk = (chunk << 4) + c;
	}


	if (ptr == buf->lr)
		goto error;

	while (http_is_spht[(unsigned char)*ptr]) {
		if (++ptr >= end)
			ptr = buf->data;
		if (ptr == buf->r)
			return 0;
	}


	while (1) {
		if (likely(HTTP_IS_CRLF(*ptr))) {

			if (likely(*ptr == '\r')) {
				if (++ptr >= end)
					ptr = buf->data;
				if (ptr == buf->r)
					return 0;
			}

			if (*ptr != '\n')
				goto error;
			if (++ptr >= end)
				ptr = buf->data;

			break;
		}
		else if (*ptr == ';') {

			if (++ptr >= end)
				ptr = buf->data;
			if (ptr == buf->r)
				return 0;

			while (!HTTP_IS_CRLF(*ptr)) {
				if (++ptr >= end)
					ptr = buf->data;
				if (ptr == buf->r)
					return 0;
			}

			continue;
		}
		else
			goto error;
	}


	msg->sov += ptr - buf->lr;
	buf->lr = ptr;
	msg->chunk_len = chunk;
	msg->body_len += chunk;
	msg->msg_state = chunk ? HTTP_MSG_DATA : HTTP_MSG_TRAILERS;
	return 1;
 error:
	msg->err_pos = ptr - buf->data;
	return -1;
}
