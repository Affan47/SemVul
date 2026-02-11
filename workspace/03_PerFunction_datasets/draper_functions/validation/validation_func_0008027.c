_unblock_signals(void)
{

	if (!_signals_blocked || _vg_lock_count)
		return;

	if (sigprocmask(SIG_SETMASK, &_oldset, NULL)) {
		log_sys_error("sigprocmask", "_block_signals");
		return;
	}

	_signals_blocked = 0;
}
