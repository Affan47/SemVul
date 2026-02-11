auth_wait(char *name, size_t name_sz)
{
    if (auth_debug_mode)
	printf(">>>%s: in auth_wait.\r\n", Name);

    if (Server && !authenticating)
	return(0);

    signal(SIGALRM, auth_intr);
    alarm(30);
    while (!authenticated)
	if (telnet_spin())
	    break;
    alarm(0);
    signal(SIGALRM, SIG_DFL);


    if (!authenticated || authenticated == &NoAuth)
	return(AUTH_REJECT);

    if (validuser == AUTH_VALID)
	validuser = AUTH_USER;

    if (authenticated->status)
	validuser = (*authenticated->status)(authenticated,
					     name, name_sz,
					     validuser);
    return(validuser);
}
