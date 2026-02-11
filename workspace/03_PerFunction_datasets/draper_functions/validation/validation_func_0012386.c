acpi_db_match_command_help(char *command,
			   const struct acpi_db_command_help *help)
{
	char *invocation = help->invocation;
	u32 line_count;


	if (*invocation != ' ') {
		return (FALSE);
	}

	while (*invocation == ' ') {
		invocation++;
	}


	while ((*command) && (*invocation) && (*invocation != ' ')) {
		if (tolower((int)*command) != tolower((int)*invocation)) {
			return (FALSE);
		}

		invocation++;
		command++;
	}


	line_count = help->line_count;
	while (line_count) {
		acpi_os_printf("%-38s : %s", help->invocation,
			       help->description);
		help++;
		line_count--;
	}

	return (TRUE);
}
