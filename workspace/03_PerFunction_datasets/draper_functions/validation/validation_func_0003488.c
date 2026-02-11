unametonum(const char * lname, int llen)
{
	char	loginname[64];
	struct passwd*	pwd;

	if (llen >= (int)sizeof(loginname)) {
		cl_log(LOG_ERR
		,	"user id name [%s] is too long", loginname);
		return -1;
	}
	strncpy(loginname, lname, llen);
	loginname[llen] = EOS;

	if (isdigit((int) loginname[0])) {
		return atoi(loginname);
	}
	if ((pwd = getpwnam(loginname)) == NULL) {
		cl_log(LOG_ERR
		,	"Invalid user id name [%s]", loginname);
		return -1;
	}
	return (int)pwd->pw_uid;
}
