invoke_edit(
    cmdarg_T	*cap,
    int		repl,
    int		cmd,
    int		startln)
{
    int		restart_edit_save = 0;


    if (repl || !stuff_empty())
	restart_edit_save = restart_edit;
    else
	restart_edit_save = 0;


    restart_edit = 0;

    if (edit(cmd, startln, cap->count1))
	cap->retval |= CA_COMMAND_BUSY;

    if (restart_edit == 0)
	restart_edit = restart_edit_save;
}
