__db_stat_print(dbp, ip, flags)
	DB *dbp;
	DB_THREAD_INFO *ip;
	u_int32_t flags;
{
	time_t now;
	int ret;
	char time_buf[CTIME_BUFLEN];

	(void)time(&now);
	__db_msg(dbp->env, "%.24s\tLocal time", __os_ctime(&now, time_buf));

	if (LF_ISSET(DB_STAT_ALL) && (ret = __db_print_all(dbp, flags)) != 0)
		return (ret);

	if ((ret = __db_print_stats(dbp, ip, flags)) != 0)
		return (ret);

	return (0);
}
