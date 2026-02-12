static int aout_core_dump(long signr, struct pt_regs * regs, struct file *file)
{
	mm_segment_t fs;
	int has_dumped = 0;
	unsigned long dump_start, dump_size;
	struct user32 dump;
#       define START_DATA(u)	(u.u_tsize << PAGE_SHIFT)
#       define START_STACK(u)   (u.start_stack)

	fs = get_fs();
	set_fs(KERNEL_DS);
	has_dumped = 1;
	current->flags |= PF_DUMPCORE;
       	strncpy(dump.u_comm, current->comm, sizeof(current->comm));
	dump.u_ar0 = (u32)(((unsigned long)(&dump.regs)) - ((unsigned long)(&dump)));
	dump.signal = signr;
	dump_thread32(regs, &dump);


	if ((dump.u_dsize+dump.u_ssize+1) * PAGE_SIZE >
	    current->signal->rlim[RLIMIT_CORE].rlim_cur)
		dump.u_dsize = 0;


	if ((dump.u_ssize+1) * PAGE_SIZE >
	    current->signal->rlim[RLIMIT_CORE].rlim_cur)
		dump.u_ssize = 0;


	set_fs(USER_DS);
	if (!access_ok(VERIFY_READ, (void *) (unsigned long)START_DATA(dump), dump.u_dsize << PAGE_SHIFT))
		dump.u_dsize = 0;
	if (!access_ok(VERIFY_READ, (void *) (unsigned long)START_STACK(dump), dump.u_ssize << PAGE_SHIFT))
		dump.u_ssize = 0;

	set_fs(KERNEL_DS);

	DUMP_WRITE(&dump,sizeof(dump));

	DUMP_SEEK(PAGE_SIZE);

	set_fs(USER_DS);

	if (dump.u_dsize != 0) {
		dump_start = START_DATA(dump);
		dump_size = dump.u_dsize << PAGE_SHIFT;
		DUMP_WRITE(dump_start,dump_size);
	}

	if (dump.u_ssize != 0) {
		dump_start = START_STACK(dump);
		dump_size = dump.u_ssize << PAGE_SHIFT;
		DUMP_WRITE(dump_start,dump_size);
	}

	set_fs(KERNEL_DS);
	DUMP_WRITE(current,sizeof(*current));
end_coredump:
	set_fs(fs);
	return has_dumped;
}
