glibtop_get_proclist_l (glibtop *server, glibtop_proclist *buf,
                        gint64 which, gint64 arg)
{
	struct {
		gint64 buf_which;
		gint64 buf_arg;
	} param_buf;

	const void *send_ptr = &param_buf;
	const size_t send_size = sizeof param_buf;
	pid_t* retval = (pid_t*) 0;
	param_buf.buf_which = which;
	param_buf.buf_arg = arg;

	glibtop_init_r (&server, (1 << GLIBTOP_SYSDEPS_PROCLIST), 0);


	if ((server->flags & _GLIBTOP_INIT_STATE_SERVER) &&
	    (server->features & (1 << GLIBTOP_SYSDEPS_PROCLIST)))
	{
		retval = glibtop_call_l (server, GLIBTOP_CMND_PROCLIST,
				         send_size, send_ptr,
				         sizeof (glibtop_proclist), buf);
	} else {
#if (!GLIBTOP_SUID_PROCLIST)
		retval = glibtop_get_proclist_s (server, buf, which, arg);
#else
		errno = ENOSYS;
		glibtop_error_io_r (server, "glibtop_get_proclist");
#endif
	}


	if (buf->flags & server->required.proclist)
		_glibtop_missing_feature (server, "proclist", buf->flags,
					  &server->required.proclist);


	return retval;
}
