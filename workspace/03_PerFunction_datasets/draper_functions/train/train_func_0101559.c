gfm_client_compound_fd_op(struct gfm_connection *gfm_server, gfarm_int32_t fd,
	gfarm_error_t (*request_op)(struct gfm_connection *, void *),
	gfarm_error_t (*result_op)(struct gfm_connection *, void *),
	void (*cleanup_op)(struct gfm_connection *, void *),
	void *closure)
{
	gfarm_error_t e;

	if ((e = gfm_client_compound_begin_request(gfm_server))
	    != GFARM_ERR_NO_ERROR)
		gflog_warning(GFARM_MSG_1000062, "compound_begin request: %s",
		    gfarm_error_string(e));
	else if ((e = gfm_client_put_fd_request(gfm_server, fd))
	    != GFARM_ERR_NO_ERROR)
		gflog_warning(GFARM_MSG_1000063, "put_fd request: %s",
		    gfarm_error_string(e));
	else if ((e = (*request_op)(gfm_server, closure))
	    != GFARM_ERR_NO_ERROR)
		;
	else if ((e = gfm_client_compound_end_request(gfm_server))
	    != GFARM_ERR_NO_ERROR)
		gflog_warning(GFARM_MSG_1000064, "compound_end request: %s",
		    gfarm_error_string(e));

	else if ((e = gfm_client_compound_begin_result(gfm_server))
	    != GFARM_ERR_NO_ERROR)
		gflog_warning(GFARM_MSG_1000065, "compound_begin result: %s",
		    gfarm_error_string(e));
	else if ((e = gfm_client_put_fd_result(gfm_server))
	    != GFARM_ERR_NO_ERROR)
		gflog_warning(GFARM_MSG_1000066, "put_fd result: %s",
		    gfarm_error_string(e));
	else if ((e = (*result_op)(gfm_server, closure))
	    != GFARM_ERR_NO_ERROR)
		;
	else if ((e = gfm_client_compound_end_result(gfm_server))
	    != GFARM_ERR_NO_ERROR) {
		gflog_warning(GFARM_MSG_1000067, "compound_end result: %s",
		    gfarm_error_string(e));
		if (cleanup_op != NULL)
			(*cleanup_op)(gfm_server, closure);
	}

	return (e);
}
