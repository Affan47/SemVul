bytecode_watchdog(void *arg)
{
    struct timeval tv;
    struct timespec out;
    int ret;
    char err[128];
    pthread_mutex_lock(&watchdog_mutex);
    if (cli_debug_flag)
	cli_dbgmsg_internal("bytecode watchdog is running\n");
    do {
	struct watchdog_item *item;
	gettimeofday(&tv, NULL);
	out.tv_sec = tv.tv_sec + WATCHDOG_IDLE;
	out.tv_nsec = tv.tv_usec*1000;

	while (watchdog_head == NULL) {
	    ret = pthread_cond_timedwait(&watchdog_cond, &watchdog_mutex,
					 &out);
	    if (ret == ETIMEDOUT)
		break;
	    if (ret) {
		cli_warnmsg("bytecode_watchdog: cond_timedwait(1) failed: %s\n",
			    cli_strerror(ret, err, sizeof(err)));
		break;
	    }
	}
	if (watchdog_head == NULL)
	    break;

	item = watchdog_head;
	while (item == watchdog_head) {
	    item->in_use = 1;
	    ret = pthread_cond_timedwait(&watchdog_cond, &watchdog_mutex,
					 &item->abstimeout);
	    if (ret == ETIMEDOUT)
		break;
	    if (ret) {
		cli_warnmsg("bytecode_watchdog: cond_timedwait(2) failed: %s\n",
			    cli_strerror(ret, err, sizeof(err)));
		break;
	    }
	}
	item->in_use = 0;
	pthread_cond_signal(&watchdog_cond2);
	if (item != watchdog_head)
	    continue;

	*item->timeout = 1;
	cli_warnmsg("[Bytecode JIT]: Bytecode run timed out, timeout flag set\n");
	watchdog_head = item->next;
	if (!watchdog_head)
	    watchdog_tail = NULL;
    } while (1);
    watchdog_running = 0;
    if (cli_debug_flag)
	cli_dbgmsg_internal("bytecode watchdog quiting\n");
    pthread_mutex_unlock(&watchdog_mutex);
    return NULL;
}
