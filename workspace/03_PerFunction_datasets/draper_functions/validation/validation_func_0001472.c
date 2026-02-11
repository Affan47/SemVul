get_my_name(aClient *cptr, char *name, int len)
{
	static	char tmp[HOSTLEN+1];
	struct	hostent	*hp;
	char	*cname = cptr->name;
	aConfItem	*aconf;
#ifdef HAVE_GETIPNODEBYNAME
	int	error_num1, error_num2;
	struct	hostent	*hp1, *hp2;
#endif


	bzero((char *)&mysk, sizeof(mysk));
	mysk.SIN_FAMILY = AFINET;
	mysk.SIN_PORT = 0;

	if ((aconf = find_me())->passwd && isdigit(*aconf->passwd))
#ifdef INET6
		if(!inetpton(AF_INET6, aconf->passwd, mysk.sin6_addr.s6_addr))
			bcopy(minus_one, mysk.sin6_addr.s6_addr, IN6ADDRSZ);
#else
		mysk.sin_addr.s_addr = inetaddr(aconf->passwd);
#endif

	if (gethostname(name, len) == -1)
		return;
	name[len] = '\0';

	add_local_domain(name, len - strlen(name));


	if (BadPtr(cname))
		return;
#ifdef HAVE_GETIPNODEBYNAME
	hp1 = getipnodebyname(cname, AF_INET6, AI_DEFAULT, &error_num1);
	hp2 = getipnodebyname(name, AF_INET6, AI_DEFAULT, &error_num2);
	if (! error_num1) hp=hp1; else hp=hp2;
	if ((! error_num1) || (! error_num2))
#else
	if ((hp = gethostbyname(cname)) || (hp = gethostbyname(name)))
#endif
	    {
		char	*hname;
		int	i = 0;

		for (hname = hp->h_name; hname; hname = hp->h_aliases[i++])
  		    {
			strncpyzt(tmp, hname, sizeof(tmp));
			add_local_domain(tmp, sizeof(tmp) - strlen(tmp));


			if (!mycmp(ME, tmp))
				break;
 		    }
		if (mycmp(ME, tmp))
			strncpyzt(name, hp->h_name, len);
		else
			strncpyzt(name, tmp, len);
#if 0


		if (BadPtr(aconf->passwd))
			bcopy(hp->h_addr, (char *)&mysk.SIN_ADDR,
			      sizeof(struct IN_ADDR));
#endif
		Debug((DEBUG_DEBUG,"local name is %s",
				get_client_name(&me,TRUE)));
	    }
#ifdef HAVE_GETIPNODEBYNAME
	freehostent(hp1);
	freehostent(hp2);
#endif
	return;
}
