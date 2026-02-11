get_commit_files_svk(const gchar * dir)
{
	enum
	{
		FIRST_CHAR,
		SKIP_SPACE,
		FILE_NAME,
	};

	gchar *txt;
	GSList *ret = NULL;
	gint pstatus = FIRST_CHAR;
	const gchar *p;
	gchar *base_name;
	const gchar *start = NULL;
	CommitItem *item;

	const gchar *status = NULL;
	gchar *filename;
	const char *argv[] = { "svk", "status", NULL };

	execute_custom_command(dir, argv, NULL, &txt, NULL, dir, NULL, NULL);
	if (!NZV(txt))
		return NULL;
	p = txt;

	while (*p)
	{
		if (*p == '\r')
		{
		}
		else if (pstatus == FIRST_CHAR)
		{
			status = NULL;
			if (*p == '?')
				status = FILE_STATUS_UNKNOWN;
			else if (*p == 'M')
				status = FILE_STATUS_MODIFIED;
			else if (*p == 'D')
				status = FILE_STATUS_DELETED;
			else if (*p == 'A')
				status = FILE_STATUS_ADDED;

			if (!status || *(p + 1) != ' ')
			{

				while (*p)
				{
					p++;
					if (*p == '\n')
					{
						p++;
						break;
					}
				}
				pstatus = FIRST_CHAR;
				continue;
			}
			pstatus = SKIP_SPACE;
		}
		else if (pstatus == SKIP_SPACE)
		{
			if (*p == ' ' || *p == '\t')
			{
			}
			else
			{
				start = p;
				pstatus = FILE_NAME;
			}
		}
		else if (pstatus == FILE_NAME)
		{
			if (*p == '\n')
			{
				if (status != FILE_STATUS_UNKNOWN)
				{
					base_name = g_malloc0(p - start + 1);
					memcpy(base_name, start, p - start);
					filename = g_build_filename(dir, base_name, NULL);
					g_free(base_name);
					item = g_new(CommitItem, 1);
					item->status = status;
					item->path = filename;
					ret = g_slist_append(ret, item);
				}
				pstatus = FIRST_CHAR;
			}
		}
		p++;
	}
	g_free(txt);
	return ret;
}
