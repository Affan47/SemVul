perf_output_sample_ustack(struct perf_output_handle *handle, u64 dump_size,
			  struct pt_regs *regs)
{

	if (!regs) {
		u64 size = 0;
		perf_output_put(handle, size);
	} else {
		unsigned long sp;
		unsigned int rem;
		u64 dyn_size;
		mm_segment_t fs;


		perf_output_put(handle, dump_size);


		sp = perf_user_stack_pointer(regs);
		fs = force_uaccess_begin();
		rem = __output_copy_user(handle, (void *) sp, dump_size);
		force_uaccess_end(fs);
		dyn_size = dump_size - rem;

		perf_output_skip(handle, rem);


		perf_output_put(handle, dyn_size);
	}
}
