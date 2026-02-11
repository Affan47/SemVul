prefix_add(char prefixes[MAX_USER_PREFIXES+1], char newprefix, SERVER_REC *server)
{
	const char *prefixlst;
	char newprefixes[MAX_USER_PREFIXES+1];
	unsigned int newpos = 0;
	unsigned int oldpos = 0;

	prefixlst = server->get_nick_flags(server);


	while (*prefixlst != '\0' && prefixes[oldpos] != '\0' &&
			newpos < MAX_USER_PREFIXES - 1) {
		if (prefixes[oldpos] == newprefix)
			return;

		if (*prefixlst == newprefix)
			break;

		if (*prefixlst == prefixes[oldpos]) {


			newprefixes[newpos++] = prefixes[oldpos++];
		}
		prefixlst++;
	}


	newprefixes[newpos++] = newprefix;


	while (prefixes[oldpos] != '\0' && newpos < MAX_USER_PREFIXES)
		newprefixes[newpos++] = prefixes[oldpos++];

	newprefixes[newpos] = '\0';

	strcpy(prefixes, newprefixes);
}
