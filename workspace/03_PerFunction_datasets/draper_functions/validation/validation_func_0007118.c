read_head_info(void)
{
	struct command **p = &commands;
	for (;;) {
		static char line[1000];
		unsigned char old_sha1[20], new_sha1[20];
		struct command *cmd;
		char *refname;
		int len, reflen;

		len = packet_read_line(0, line, sizeof(line));
		if (!len)
			break;
		if (line[len-1] == '\n')
			line[--len] = 0;
		if (len < 83 ||
		    line[40] != ' ' ||
		    line[81] != ' ' ||
		    get_sha1_hex(line, old_sha1) ||
		    get_sha1_hex(line + 41, new_sha1))
			die("protocol error: expected old/new/ref, got '%s'",
			    line);

		refname = line + 82;
		reflen = strlen(refname);
		if (reflen + 82 < len) {
			if (strstr(refname + reflen + 1, "report-status"))
				report_status = 1;
		}
		cmd = xmalloc(sizeof(struct command) + len - 80);
		hashcpy(cmd->old_sha1, old_sha1);
		hashcpy(cmd->new_sha1, new_sha1);
		memcpy(cmd->ref_name, line + 82, len - 81);
		cmd->error_string = NULL;
		cmd->next = NULL;
		*p = cmd;
		p = &cmd->next;
	}
}
