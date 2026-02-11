read_from_stdin(struct shortlog *log)
{
	char author[1024], oneline[1024];

	while (fgets(author, sizeof(author), stdin) != NULL) {
		if (!(author[0] == 'A' || author[0] == 'a') ||
		    prefixcmp(author + 1, "uthor: "))
			continue;
		while (fgets(oneline, sizeof(oneline), stdin) &&
		       oneline[0] != '\n')
			;
		while (fgets(oneline, sizeof(oneline), stdin) &&
		       oneline[0] == '\n')
			;
		insert_one_record(log, author + 8, oneline);
	}
}
