cfg_read_config_file(ConfigFile *cf, char *filename)
{
	FILE *file;
	char ch;
	int bufcnt;
	char key_buffer[128] = "", value_buffer[128] = "";


	file = fopen(filename, "r");
	if (file)
	{
		while(!feof(file))
		{
			ch = fgetc(file);

			if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n')
				while (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n') ch = fgetc(file);

			do {
				if (ch == '#') {
					while (ch != '\n' && ch != '\r') ch = fgetc(file);
					ch = fgetc(file);
				}
				if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
					ch = fgetc(file);
			} while (ch == '#' || ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r');

			bufcnt = 0;

			while (ch != ' ' && ch != '\t' && ch != '\n' && ch != '\r' &&
			       ch != '=' && !feof(file) && bufcnt < 126)
			{
				key_buffer[bufcnt] = ch;
				bufcnt++;
				ch = fgetc(file);
			}
			key_buffer[bufcnt] = '\0';

			while (ch != '=' && !feof(file))
			{
				ch = fgetc(file);
			}
			ch = fgetc(file);


			if (ch == ' ' || ch == '\t')
				while (ch == ' ' || ch == '\t') ch = fgetc(file);


			bufcnt = 0;
			while (ch != '\n' && ch != '\r' && !feof(file) &&
			       !feof(file) && bufcnt < 126)
			{
				value_buffer[bufcnt] = ch;
				bufcnt++;
				ch = fgetc(file);
			}
			value_buffer[bufcnt] = '\0';

			if (strlen(key_buffer) > 0)
				cfg_add_key(cf, key_buffer, value_buffer);
		}
		fclose(file);
	}
	else
	{
		printf("config: Cannot open config file!\n");
		return -2;
	}
	return 0;
}
