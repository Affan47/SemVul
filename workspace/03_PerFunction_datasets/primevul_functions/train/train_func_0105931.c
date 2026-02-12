int vt_move_to_console(unsigned int vt, int alloc)
{
	int prev;

	console_lock();

	if (disable_vt_switch) {
		console_unlock();
		return 0;
	}
	prev = fg_console;

	if (alloc && vc_allocate(vt)) {


		console_unlock();
		return -ENOSPC;
	}

	if (set_console(vt)) {


		console_unlock();
		return -EIO;
	}
	console_unlock();
	if (vt_waitactive(vt + 1)) {
		pr_debug("Suspend: Can't switch VCs.");
		return -EINTR;
	}
	return prev;
}
