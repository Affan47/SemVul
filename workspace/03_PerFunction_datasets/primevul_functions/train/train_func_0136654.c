static int perf_event_set_bpf_handler(struct perf_event *event, u32 prog_fd)
{
	struct bpf_prog *prog;

	if (event->overflow_handler_context)

		return -EINVAL;

	if (event->prog)
		return -EEXIST;

	prog = bpf_prog_get_type(prog_fd, BPF_PROG_TYPE_PERF_EVENT);
	if (IS_ERR(prog))
		return PTR_ERR(prog);

	if (event->attr.precise_ip &&
	    prog->call_get_stack &&
	    (!(event->attr.sample_type & __PERF_SAMPLE_CALLCHAIN_EARLY) ||
	     event->attr.exclude_callchain_kernel ||
	     event->attr.exclude_callchain_user)) {


		bpf_prog_put(prog);
		return -EPROTO;
	}

	event->prog = prog;
	event->orig_overflow_handler = READ_ONCE(event->overflow_handler);
	WRITE_ONCE(event->overflow_handler, bpf_overflow_handler);
	return 0;
}
