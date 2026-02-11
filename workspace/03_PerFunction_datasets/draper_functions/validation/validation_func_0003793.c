undo_signals(const struct signal *signals, int num_signals, int which)
{
    int error = 0;
    int i;

    for (i = num_signals - 1; i >= 0; i--) {
	const struct signal *s = &signals[i];

	if (s->which != which)
	    continue;

	if (!s->valid)
	    continue;

	switch (s->action) {
	case SSA_IGNORE:
	case SSA_DEFAULT:
	    if (sigaction(s->signum, &s->old_act, NULL) < 0) {
		G_warning(_("G_spawn: unable to restore signal %d"),
			  s->signum);
		error = 1;
	    }
	    break;
	case SSA_BLOCK:
	case SSA_UNBLOCK:
	    if (sigprocmask(SIG_UNBLOCK, &s->old_mask, NULL) < 0) {
		G_warning(_("G_spawn: unable to restore signal %d"),
			  s->signum);
		error = 1;
	    }
	    break;
	}
    }

    return !error;
}
