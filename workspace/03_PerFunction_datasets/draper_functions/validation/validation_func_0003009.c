Proc_isAlive(CTX ctx, ksfp_t *sfp _RIX)
{
	knh_Proc_t *sp = (knh_Proc_t *)sfp[0].o;
	int status = 0;
	pid_t ret = 0;
	errno = 0;
	ret = waitpid(sp->pid, &status, WNOHANG);
	if (ret == -1) {
		KNH_NTHROW2(ctx, sfp, "System!!", "waitpid", K_PERROR, KNH_LDATA0);
	} else {
		if (ret != 0) {

			DBG_P("process already died, close fds");
			Proc_free(ctx, (kRawPtr *)sp);
		}
		DBG_P("ret=%d", ret);
		DBG_P("WIFEXITED=%s", WIFEXITED(status) ? "true" : "false");
		DBG_P("WEXITSTATUS=%d", WEXITSTATUS(status));
		DBG_P("WIFSIGNALED=%s", WIFSIGNALED(status) ? "true" : "false");
		DBG_P("WTERMSIG=%d", WIFSIGNALED(status) ? WTERMSIG(status) : -1);
		DBG_P("WCOREDUMP=%s", WIFSIGNALED(status) ? (WCOREDUMP(status) ? "true" : "false") : "none");
		DBG_P("WIFSTOPPED=%s", WIFSTOPPED(status) ? "true" : "false");
		DBG_P("WSTOPSIG=%d", WIFSTOPPED(status) ? WSTOPSIG(status) : -1);
	}
	RETURNb_((ret == 0) ? 1 : 0);
}
