cache_sim_read_skipline(FILE *f, gint s)
{
	if (!f) return FALSE;

	if (fseek(f, 0 - s, SEEK_CUR) == 0)
		{
		gchar b;
		while (fread(&b, sizeof(b), 1, f) == 1)
			{
			if (b == '\n') return TRUE;
			}
		return TRUE;
		}

	return FALSE;
}
