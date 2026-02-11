parse_out_relatives(gchar *path)
{
	gint s, t;

	if (!path) return;

	s = t = 0;

	while (path[s] != '\0')
		{
		if (path[s] == G_DIR_SEPARATOR && path[s+1] == '.')
			{

			gint p = s + 2;

			if (path[p] == G_DIR_SEPARATOR || path[p] == '\0')
				{

				s = p;
				continue;
				}
			else if (path[p] == '.' && (path[p+1] == G_DIR_SEPARATOR || path[p+1] == '\0'))
				{

				s = p + 1;
				if (t > 0) t--;
				while (path[t] != G_DIR_SEPARATOR && t > 0) t--;
				continue;
				}
			}

		if (s != t) path[t] = path[s];
		t++;
		s++;
		}

	if (t == 0 && path[t] == G_DIR_SEPARATOR) t++;
	if (t > 1 && path[t-1] == G_DIR_SEPARATOR) t--;
	path[t] = '\0';
}
