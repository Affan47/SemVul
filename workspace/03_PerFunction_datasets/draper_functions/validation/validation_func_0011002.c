process_userpass(char *userpass, char **username, char **password) {
	int nargs;
	char **args;

	if(string_split(userpass,&nargs,&args)) {
		if(!*username) *username = strdup(args[0]);
		if(!*password) *password = strdup(args[1]);
		free(args);
		return 0;
	}
	return -1;
}
