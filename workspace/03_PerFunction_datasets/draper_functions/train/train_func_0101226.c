get_commit_info(struct commit *commit,
			    struct commit_info *ret,
			    int detailed)
{
	int len;
	const char *subject;
	char *reencoded, *message;
	static char author_name[1024];
	static char author_mail[1024];
	static char committer_name[1024];
	static char committer_mail[1024];
	static char summary_buf[1024];


	if (!commit->buffer) {
		enum object_type type;
		unsigned long size;
		commit->buffer =
			read_sha1_file(commit->object.sha1, &type, &size);
		if (!commit->buffer)
			die("Cannot read commit %s",
			    sha1_to_hex(commit->object.sha1));
	}
	reencoded = reencode_commit_message(commit, NULL);
	message   = reencoded ? reencoded : commit->buffer;
	ret->author = author_name;
	ret->author_mail = author_mail;
	get_ac_line(message, "\nauthor ",
		    sizeof(author_name), author_name,
		    sizeof(author_mail), author_mail,
		    &ret->author_time, &ret->author_tz);

	if (!detailed) {
		free(reencoded);
		return;
	}

	ret->committer = committer_name;
	ret->committer_mail = committer_mail;
	get_ac_line(message, "\ncommitter ",
		    sizeof(committer_name), committer_name,
		    sizeof(committer_mail), committer_mail,
		    &ret->committer_time, &ret->committer_tz);

	ret->summary = summary_buf;
	len = find_commit_subject(message, &subject);
	if (len && len < sizeof(summary_buf)) {
		memcpy(summary_buf, subject, len);
		summary_buf[len] = 0;
	} else {
		sprintf(summary_buf, "(%s)", sha1_to_hex(commit->object.sha1));
	}
	free(reencoded);
}
