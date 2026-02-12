ca_run(struct privsep *ps, struct privsep_proc *p, void *arg)
{
	struct iked	*env = ps->ps_env;
	struct ca_store	*store;


	if (pledge("stdio rpath recvfd", NULL) == -1)
		fatal("pledge");

	if ((store = calloc(1, sizeof(*store))) == NULL)
		fatal("%s: failed to allocate cert store", __func__);

	env->sc_priv = store;
	p->p_shutdown = ca_shutdown;
}
