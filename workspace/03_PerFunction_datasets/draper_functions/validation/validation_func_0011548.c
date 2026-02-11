add_pid(const pid_t pid)
{
	pid_list **curr = &G.pid_list_head;

	while (*curr) {
		if ((*curr)->pid == pid)
			return;
		curr = &(*curr)->next;
	}

	*curr = xzalloc(sizeof(pid_list));
	(*curr)->pid = pid;
}
