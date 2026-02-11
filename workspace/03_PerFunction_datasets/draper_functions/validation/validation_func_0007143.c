parse_conf_line (const gchar *line, gchar *str)
{
	int i;
	int j;
	gboolean found = FALSE;

	for (i = 0; i <= 99; i++) {

		if (line[i] == '=' && found == FALSE) {
			int start = i + 2;
			found = TRUE;

			for (j = start; j <= 99; j++) {

				if ( line[j] != '\n' )
					str[j - start] = line[j];
				else
					str[j - start] = '\0';
			}
		}
	}

	return str;
}
