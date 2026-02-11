list_commands(const char *title, struct cmdnames *main_cmds,
		   struct cmdnames *other_cmds)
{
	int i, longest = 0;

	for (i = 0; i < main_cmds->cnt; i++)
		if (longest < main_cmds->names[i]->len)
			longest = main_cmds->names[i]->len;
	for (i = 0; i < other_cmds->cnt; i++)
		if (longest < other_cmds->names[i]->len)
			longest = other_cmds->names[i]->len;

	if (main_cmds->cnt) {
		const char *exec_path = git_exec_path();
		printf("available %s in '%s'\n", title, exec_path);
		printf("----------------");
		mput_char('-', strlen(title) + strlen(exec_path));
		putchar('\n');
		pretty_print_string_list(main_cmds, longest);
		putchar('\n');
	}

	if (other_cmds->cnt) {
		printf("%s available from elsewhere on your $PATH\n", title);
		printf("---------------------------------------");
		mput_char('-', strlen(title));
		putchar('\n');
		pretty_print_string_list(other_cmds, longest);
		putchar('\n');
	}
}
