static inline int htx_copy_msg(struct htx *htx, const struct buffer *msg)
{

	if (htx_is_empty(htx)) {
		memcpy(htx, msg->area, msg->size);
		return 1;
	}


	return htx_append_msg(htx, htxbuf(msg));
}
