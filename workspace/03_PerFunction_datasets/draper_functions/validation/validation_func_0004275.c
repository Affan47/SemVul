_plugin_stack_parse_line(char *line, char **plugin, int *acp, char ***argv,
			 cf_line_t * type)
{
	int ac;
	const char *separators = " \t\n";
	char *path;
	char *option;
	char *s;
	char **av;
	char *sp;

	*plugin = NULL;
	*argv = NULL;
	*acp = 0;


	if ((s = strchr(line, '#')))
		*s = '\0';

	if (!(option = strtok_r(line, separators, &sp)))
		return (0);

	if (((*type) = _plugin_stack_line_type(option)) == CF_ERROR)
		return (-1);

	if (!(path = strtok_r(NULL, separators, &sp)))
		return (-1);

	ac = 0;
	av = NULL;

	while ((s = strtok_r(NULL, separators, &sp)))
		_argv_append(&av, ac++, s);

	*plugin = xstrdup(path);
	*argv = av;
	*acp = ac;

	return (0);
}
