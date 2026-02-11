stop_children()
{
    int i;
    if (!childtab)
	return;
    stop_all(SIGTERM);
    for (i = 0; i < shutdown_timeout; i++) {
	cleanup_children(1);
	if (num_children == 0)
	    return;
	sleep(1);
    }
    stop_all(SIGKILL);
}
