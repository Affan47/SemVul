set_thread_local_context(const thread_local_context_ptr &ctx) {
		local_context = new thread_local_context_ptr(ctx);
	}
