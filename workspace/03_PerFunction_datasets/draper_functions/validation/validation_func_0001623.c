check_allThreadExit(CTX ctx)
{
	int i;
	KNH_SYSLOCK(ctx);
	ctx->wshare->stopCounter++;
	if(ctx->share->gcStopCounter != 0) {
		kthread_cond_signal(ctx->share->start_cond);
	}
	if(ctx->share->threadCounter != 1) {
		kthread_cond_wait(ctx->share->close_cond, ctx->share->syslock);
	}
	for(i = knh_Array_size(ctx->share->contextListNULL) - 1; i >= 0; i--) {
		kContext *c = (kContext *)knh_Array_n(ctx->share->contextListNULL, i);
		if(c->ctx != ctx) {
			knh_Context_free(ctx, WCTX(c->ctx));
			knh_Array_remove(ctx, ctx->share->contextListNULL, i);
		}
	}
	KNH_SYSUNLOCK(ctx);
}
