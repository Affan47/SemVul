output_open(void)
{
	int waitstatus, waitret;

	if (!(pc->flags & TTY))
		return TRUE;

	switch (pc->redirect & PIPE_OPTIONS)
	{
	case (REDIRECT_TO_STDPIPE|FROM_COMMAND_LINE):
		waitret = waitpid(pc->stdpipe_pid, &waitstatus, WNOHANG);
		if ((waitret == pc->stdpipe_pid) || (waitret == -1))
               		return FALSE;
		break;

	case (REDIRECT_TO_PIPE|FROM_INPUT_FILE):
		if (pc->curcmd_flags & REPEAT)
			break;

	case (REDIRECT_TO_PIPE|FROM_COMMAND_LINE):
		switch (pc->redirect & (REDIRECT_MULTI_PIPE))
		{
		case REDIRECT_MULTI_PIPE:
			if (!PID_ALIVE(pc->pipe_pid))
				return FALSE;
			break;

		default:
               		waitret = waitpid(pc->pipe_pid, &waitstatus, WNOHANG);
                	if (waitret == pc->pipe_pid)
                        	return FALSE;
			if (waitret == -1) {
				if (!PID_ALIVE(pc->pipe_pid))
					return FALSE;
			}
			break;
		}
		break;

	default:
		break;
	}

	return TRUE;
}
