mo_kill(struct Client *client_p, struct Client *source_p, int parc, const char *parv[])
{
	struct Client *target_p;
	const char *inpath = client_p->name;
	const char *user;
	const char *reason;

	user = parv[1];

	if(!IsOperLocalKill(source_p))
	{
		sendto_one(source_p, form_str(ERR_NOPRIVS), me.name, source_p->name, "local_kill");
		return 0;
	}

	if(!EmptyString(parv[2]))
	{
		char *s;
		s = LOCAL_COPY(parv[2]);
		if(strlen(s) > (size_t) KILLLEN)
			s[KILLLEN] = '\0';
		reason = s;
	}
	else
		reason = "<No reason given>";

	if((target_p = find_named_person(user)) == NULL)
	{


		if((target_p = get_history(user, (long) KILLCHASETIMELIMIT)) == NULL)
		{
			if (strchr(user, '.'))
				sendto_one_numeric(source_p, ERR_CANTKILLSERVER, form_str(ERR_CANTKILLSERVER));
			else
				sendto_one_numeric(source_p, ERR_NOSUCHNICK,
						   form_str(ERR_NOSUCHNICK), user);
			return 0;
		}
		sendto_one_notice(source_p, ":KILL changed from %s to %s", user, target_p->name);
	}

	if(!MyConnect(target_p) && (!IsOperGlobalKill(source_p)))
	{
		sendto_one_notice(source_p, ":Nick %s is not on your server "
				            "and you do not have the global_kill flag",
				target_p->name);
		return 0;
	}

	if(MyConnect(target_p))
		sendto_one(target_p, ":%s!%s@%s KILL %s :%s",
			   source_p->name, source_p->username, source_p->host,
			   target_p->name, reason);


	sendto_realops_snomask(SNO_GENERAL, L_ALL,
			     "Received KILL message for %s!%s@%s. From %s Path: %s (%s)",
			     target_p->name, target_p->username, target_p->orighost,
			     source_p->name, me.name, reason);

	ilog(L_KILL, "%c %s %s!%s@%s %s %s",
	     MyConnect(target_p) ? 'L' : 'G', get_oper_name(source_p),
	     target_p->name, target_p->username, target_p->host, target_p->servptr->name, reason);


	if(!MyConnect(target_p))
	{
		relay_kill(client_p, source_p, target_p, inpath, reason);


		target_p->flags |= FLAGS_KILLED;
	}

	rb_sprintf(buf, "Killed (%s (%s))", source_p->name, reason);

	exit_client(client_p, target_p, source_p, buf);

	return 0;
}
