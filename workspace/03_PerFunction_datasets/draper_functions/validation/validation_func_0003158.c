cache_user_motd(void)
{
	struct stat sb;
	struct tm *local_tm;

	if(stat(MPATH, &sb) == 0)
	{
		local_tm = localtime(&sb.st_mtime);

		if(local_tm != NULL)
		{
			rb_snprintf(user_motd_changed, sizeof(user_motd_changed),
				 "%d/%d/%d %d:%d",
				 local_tm->tm_mday, local_tm->tm_mon + 1,
				 1900 + local_tm->tm_year, local_tm->tm_hour,
				 local_tm->tm_min);
		}
	}
	free_cachefile(user_motd);
	user_motd = cache_file(MPATH, "ircd.motd", 0);
}
