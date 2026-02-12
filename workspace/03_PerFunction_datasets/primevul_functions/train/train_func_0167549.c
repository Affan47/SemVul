int http_forward_trailers(struct buffer *buf, struct http_msg *msg)
{

	while (1) {
		char *p1 = NULL, *p2 = NULL;
		char *ptr = buf->lr;
		int bytes;


		while (1) {
			if (ptr == buf->r)
				return 0;

			if (*ptr == '\n') {
				if (!p1)
					p1 = ptr;
				p2 = ptr;
				break;
			}

			if (*ptr == '\r') {
				if (p1) {
					msg->err_pos = ptr - buf->data;
					return -1;
				}
				p1 = ptr;
			}

			ptr++;
			if (ptr >= buf->data + buf->size)
				ptr = buf->data;
		}


		p2++;
		if (p2 >= buf->data + buf->size)
			p2 = buf->data;

		bytes = p2 - buf->lr;
		if (bytes < 0)
			bytes += buf->size;


		msg->sov += bytes;
		if (msg->sov >= buf->size)
			msg->sov -= buf->size;

		if (p1 == buf->lr) {


			buf->lr = p2;
			msg->msg_state = HTTP_MSG_DONE;
			return 1;
		}

		buf->lr = p2;
	}
}
