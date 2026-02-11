__rpc_thread_variables (void)
{
	__libc_once_define (static, once);
	struct rpc_thread_variables *tvp;

	tvp = __libc_tsd_get (struct rpc_thread_variables *, RPC_VARS);
	if (tvp == NULL) {
		__libc_once (once, rpc_thread_multi);
		tvp = __libc_tsd_get (struct rpc_thread_variables *, RPC_VARS);
		if (tvp == NULL) {
			tvp = calloc (1, sizeof *tvp);
			if (tvp != NULL)
				__libc_tsd_set (struct rpc_thread_variables *,
						RPC_VARS, tvp);
			else
				tvp = __libc_tsd_get (struct rpc_thread_variables *,
						      RPC_VARS);
		}
	}
	return tvp;
}
