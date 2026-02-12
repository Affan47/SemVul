static int http_handle_expect_hdr(struct stream *s, struct htx *htx, struct http_msg *msg)
{


	if (msg->msg_state == HTTP_MSG_BODY && (msg->flags & HTTP_MSGF_VER_11) &&
	    (msg->flags & (HTTP_MSGF_CNT_LEN|HTTP_MSGF_TE_CHNK))) {
		struct ist hdr = { .ptr = "Expect", .len = 6 };
		struct http_hdr_ctx ctx;

		ctx.blk = NULL;

		if (http_find_header(htx, hdr, &ctx, 0) &&
		    unlikely(isteqi(ctx.value, ist2("100-continue", 12)))) {
			if (http_reply_100_continue(s) == -1)
				return -1;
			http_remove_header(htx, &ctx);
		}
	}
	return 0;
}
