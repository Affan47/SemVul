cri_rstrt_hndl_child_main(int token, int threads, int flags) {
    struct sigaction sa;
    uintptr_t incr = sysconf(_SC_PAGESIZE);
    uintptr_t stack;
    int err;
    int i;


    sa.sa_sigaction = cri_omit_sig_handler;
    sa.sa_flags = SA_RESTART | SA_SIGINFO;
    (void)sigfillset(&sa.sa_mask);
    (void)sigaction(CR_SIGNUM, &sa, NULL);

    if (threads > 1) {
	stack = (uintptr_t)mmap(0, (threads - 1) * incr, PROT_READ | PROT_WRITE | PROT_EXEC,
				MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	if ((void *)stack == MAP_FAILED) {
	    fprintf(stderr, "Failed to allocate stack space for child thread(s)\n");
	    exit(1);
	}
#if (CR_STACK_GROWTH < 0)
	stack += incr;
#elif (CR_STACK_GROWTH > 0)

#else
	#error "Don't know which way the stack grows"
#endif

        for (i = 1; i < threads; ++i) {
	    err = clone(&cri_rstrt_hndl_child_inner, (void *)stack, flags, (void *)(uintptr_t)token);
	    if (err < 0) {
	        fprintf(stderr, "clone() failed while creating child thread(s)\n");
	        exit(1);
	    }
	    stack += incr;
	}
    }

    cri_rstrt_hndl_child_inner((void *)(uintptr_t)token);


    return 0;
}
