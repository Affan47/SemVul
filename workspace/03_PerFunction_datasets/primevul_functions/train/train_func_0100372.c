int flush_old_exec(struct linux_binprm * bprm)
{
	char * name;
	int i, ch, retval;
	struct files_struct *files;
	char tcomm[sizeof(current->comm)];


	retval = de_thread(current);
	if (retval)
		goto out;


	files = current->files;
	retval = unshare_files();
	if (retval)
		goto out;


	retval = exec_mmap(bprm->mm);
	if (retval)
		goto mmap_failed;

	bprm->mm = NULL;


	put_files_struct(files);

	current->sas_ss_sp = current->sas_ss_size = 0;

	if (current->euid == current->uid && current->egid == current->gid)
		current->mm->dumpable = 1;
	else
		current->mm->dumpable = suid_dumpable;

	name = bprm->filename;


	for (i=0; (ch = *(name++)) != '\0';) {
		if (ch == '/')
			i = 0;
		else
			if (i < (sizeof(tcomm) - 1))
				tcomm[i++] = ch;
	}
	tcomm[i] = '\0';
	set_task_comm(current, tcomm);

	current->flags &= ~PF_RANDOMIZE;
	flush_thread();


	current->mm->task_size = TASK_SIZE;

	if (bprm->e_uid != current->euid || bprm->e_gid != current->egid ||
	    file_permission(bprm->file, MAY_READ) ||
	    (bprm->interp_flags & BINPRM_FLAGS_ENFORCE_NONDUMP)) {
		suid_keys(current);
		current->mm->dumpable = suid_dumpable;
	}


	current->self_exec_id++;

	flush_signal_handlers(current, 0);
	flush_old_files(current->files);

	return 0;

mmap_failed:
	reset_files_struct(current, files);
out:
	return retval;
}
