n_access_del(struct Luser *lptr, struct NickInfo *target, int ac, char **av)

{
	struct NickInfo *nptr;
	struct NickHost *hptr, *prev;
	int found;
	char *mask;

	if (target)
	{
		if (ac < 4)
		{
			notice(n_NickServ, lptr->nick,
				   "Syntax: \002ACCESS <nickname> DEL <mask>\002");
			notice(n_NickServ, lptr->nick,
				   ERR_MORE_INFO,
				   n_NickServ,
				   "ACCESS DEL");
			return;
		}

		nptr = target;
		mask = av[3];
	}
	else
	{
		if (ac < 3)
		{
			notice(n_NickServ, lptr->nick,
				   "Syntax: \002ACCESS DEL <mask>\002");
			notice(n_NickServ, lptr->nick,
				   ERR_MORE_INFO,
				   n_NickServ,
				   "ACCESS DEL");
			return;
		}

		nptr = GetLink(lptr->nick);
		mask = av[2];
	}

	if (!nptr)
		return;

	found = 0;

	prev = NULL;
	for (hptr = nptr->hosts; hptr; )
	{
		if (match(mask, hptr->hostmask))
		{
			found = 1;
			MyFree(hptr->hostmask);

			if (prev)
			{
				prev->next = hptr->next;
				MyFree(hptr);
				hptr = prev;
			}
			else
			{
				nptr->hosts = hptr->next;
				MyFree(hptr);
				hptr = NULL;
			}

			break;
		}

		prev = hptr;
		hptr = hptr->next;
	}

	if (found)
	{
		if (target)
		{
			notice(n_NickServ, lptr->nick,
				   "[\002%s\002] removed from the Access List for [%s]",
				   mask,
				   target->nick);

			RecordCommand("%s: Administrator %s!%s@%s ACCESS %s DEL [%s]",
						  n_NickServ,
						  lptr->nick,
						  lptr->username,
						  lptr->hostname,
						  target->nick,
						  mask);
		}
		else
		{
			notice(n_NickServ, lptr->nick,
				   "[\002%s\002] removed from your Access List",
				   mask);

			RecordCommand("%s: %s!%s@%s ACCESS DEL [%s]",
						  n_NickServ,
						  lptr->nick,
						  lptr->username,
						  lptr->hostname,
						  mask);
		}
	}
	else
	{
		if (target)
			notice(n_NickServ, lptr->nick,
				   "[\002%s\002] was not found on the Acces List for [%s]",
				   mask,
				   target->nick);
		else
			notice(n_NickServ, lptr->nick,
				   "[\002%s\002] was not found on your Access List",
				   mask);
	}
}
