init_offsets(void)
{
#define init_offset(struct, member) do {				\
		koffset(struct, member) = MEMBER_OFFSET(#struct, #member);\
		if (koffset(struct, member) < 0) {			\
			fprintf(fp, "failed to init the offset, struct:"\
				#struct ", member:" #member);		\
			return -1;					\
		}							\
	} while (0)


	init_offset(trace_array, buffer);
	init_offset(tracer, name);

	if (MEMBER_EXISTS("ring_buffer_per_cpu", "nr_pages")) {
		per_cpu_buffer_sizes = 1;
		if (verbose)
			fprintf(fp, "per cpu buffer sizes\n");
	}

	if (!per_cpu_buffer_sizes)
		init_offset(ring_buffer, pages);
	init_offset(ring_buffer, flags);
	init_offset(ring_buffer, cpus);
	init_offset(ring_buffer, buffers);

	if (MEMBER_SIZE("ring_buffer_per_cpu", "pages") == sizeof(ulong)) {
		lockless_ring_buffer = 1;
		if (verbose)
			fprintf(fp, "lockless\n");
	}

	if (per_cpu_buffer_sizes)
		init_offset(ring_buffer_per_cpu, nr_pages);
	init_offset(ring_buffer_per_cpu, cpu);
	init_offset(ring_buffer_per_cpu, pages);
	init_offset(ring_buffer_per_cpu, head_page);
	init_offset(ring_buffer_per_cpu, tail_page);
	init_offset(ring_buffer_per_cpu, commit_page);
	init_offset(ring_buffer_per_cpu, reader_page);
	init_offset(ring_buffer_per_cpu, overrun);
	init_offset(ring_buffer_per_cpu, entries);

	init_offset(buffer_page, read);
	init_offset(buffer_page, list);
	init_offset(buffer_page, page);

	init_offset(list_head, next);

	init_offset(ftrace_event_call, list);

	init_offset(ftrace_event_field, link);
	init_offset(ftrace_event_field, name);
	init_offset(ftrace_event_field, type);
	init_offset(ftrace_event_field, offset);
	init_offset(ftrace_event_field, size);
	init_offset(ftrace_event_field, is_signed);

	return 0;
#undef init_offset
}
