sshpam_free_ctx(void *ctxtp)
{
	struct pam_ctxt *ctxt = ctxtp;

	fatal_remove_cleanup(sshpam_thread_cleanup, ctxt);
	sshpam_thread_cleanup(ctxtp);
	xfree(ctxt);


}
