c_clear_modes(struct Luser *lptr, struct NickInfo *nptr, int ac, char **av)

{
	char modes[MAXLINE + 1];
	struct Channel *chptr;

	if (!(chptr = FindChannel(av[1])))
	{
		notice(n_ChanServ, lptr->nick,
		       "The channel [\002%s\002] is not active",
		       av[1]);
		return;
	}

	strlcpy(modes, "-", sizeof(modes));

	if (chptr->modes & MODE_S)
		strlcat(modes, "s", sizeof(modes));
	if (chptr->modes & MODE_P)
		strlcat(modes, "p", sizeof(modes));
	if (chptr->modes & MODE_N)
		strlcat(modes, "n", sizeof(modes));
	if (chptr->modes & MODE_T)
		strlcat(modes, "t", sizeof(modes));
#ifdef DANCER

	if (chptr->modes & MODE_C)
		strlcat(modes, "c", sizeof(modes));
#endif

	if (chptr->modes & MODE_M)
		strlcat(modes, "m", sizeof(modes));
	if (chptr->modes & MODE_I)
		strlcat(modes, "i", sizeof(modes));
	if (chptr->limit)
		strlcat(modes, "l", sizeof(modes));
	if (chptr->key[0] != '\0')
	{
		strlcat(modes, "k ", sizeof(modes));
		strlcat(modes, chptr->key, sizeof(modes));
	}
#ifdef DANCER
	if (chptr->forward)
	{
		strlcat(modes, "f ", sizeof(modes));
		strlcat(modes, chptr->forward, sizeof(modes));
	}
#endif

	toserv(":%s MODE %s %s\r\n", n_ChanServ, chptr->name, modes);

	UpdateChanModes(Me.csptr, n_ChanServ, chptr, modes);
}
