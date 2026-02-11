parse_from_header( struct sip_msg *msg)
{
	struct to_body* from_b;

	if ( !msg->from && ( parse_headers(msg,HDR_FROM_F,0)==-1 || !msg->from)) {
		LM_ERR("bad msg or missing FROM header\n");
		goto error;
	}


	if (msg->from->parsed)
		return 0;


	from_b = pkg_malloc(sizeof(struct to_body));
	if (from_b == 0) {
		LM_ERR("out of pkg_memory\n");
		goto error;
	}


	memset(from_b, 0, sizeof(struct to_body));
	parse_to(msg->from->body.s,msg->from->body.s+msg->from->body.len+1,from_b);
	if (from_b->error == PARSE_ERROR) {
		LM_ERR("bad from header\n");
		pkg_free(from_b);
		set_err_info(OSER_EC_PARSER, OSER_EL_MEDIUM,
			"error parsing From header");
		set_err_reply(400, "bad header");
		goto error;
	}


	msg->from->parsed = from_b;

	return 0;
error:
	return -1;
}
