net_query_host(void)
{
	static char *s = CN;

	if (CONNECTED) {
		Free(s);

#if defined(LOCAL_PROCESS)
		if (local_process) {
			s = xs_buffer("process %s", hostname);
		} else
#endif
		{
			s = xs_buffer("host %s %u %s",
					hostname, current_port,
#if defined(HAVE_LIBSSL)
					secure_connection? "encrypted":
#endif
							   "unencrypted"
					    );
		}
		return s;
	} else
		return "";
}
