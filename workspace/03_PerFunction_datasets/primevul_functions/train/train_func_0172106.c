parse_user_name(char *user_input, char **ret_username)
{
	register char *ptr;
	register int index = 0;
	char username[PAM_MAX_RESP_SIZE];


	*ret_username = NULL;


	bzero((void *)username, PAM_MAX_RESP_SIZE);


	ptr = user_input;


	while ((*ptr == ' ') || (*ptr == '\t'))
		ptr++;

	if (*ptr == '\0') {


		return (PAM_BUF_ERR);
	}


	while (*ptr != '\0') {
		if ((*ptr == ' ') || (*ptr == '\t') ||
		    (index >= PAM_MAX_RESP_SIZE)) {
			break;
		} else {
			username[index] = *ptr;
			index++;
			ptr++;
		}
	}


	if (index >= PAM_MAX_RESP_SIZE ||
	    (*ret_username = strdup(username)) == NULL)
		return (PAM_BUF_ERR);
	return (PAM_SUCCESS);
}
