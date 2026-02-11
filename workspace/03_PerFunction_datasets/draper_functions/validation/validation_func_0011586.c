processes_killall(int signum)
{
	GSList *tmp;

	for (tmp = processes; tmp != NULL; tmp = tmp->next) {
		PROCESS_REC *rec = tmp->data;

		kill(rec->pid, signum);
	}
}
