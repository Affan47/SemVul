handle_certfp(sourceinfo_t *si, user_t *u, const char *certfp)
{
	myuser_t *mu;
	mycertfp_t *mcfp;
	service_t *svs;

	free(u->certfp);
	u->certfp = sstrdup(certfp);

	if (u->myuser != NULL)
		return;

	if ((mcfp = mycertfp_find(certfp)) == NULL)
		return;

	mu = mcfp->mu;
	svs = nicksvs.me;
	if (svs == NULL)
		return;

	if (metadata_find(mu, "private:freeze:freezer"))
	{
		notice(svs->me->nick, u->nick, nicksvs.no_nick_ownership ? "You cannot login as \2%s\2 because the account has been frozen." : "You cannot identify to \2%s\2 because the nickname has been frozen.", entity(mu)->name);
		logcommand_user(svs, u, CMDLOG_LOGIN, "failed LOGIN to %s (frozen) via CERTFP (%s)", entity(mu)->name, certfp);
		return;
	}

	if (MOWGLI_LIST_LENGTH(&mu->logins) >= me.maxlogins)
	{
		notice(svs->me->nick, u->nick, _("There are already \2%zu\2 sessions logged in to \2%s\2 (maximum allowed: %u)."), MOWGLI_LIST_LENGTH(&mu->logins), entity(mu)->name, me.maxlogins);
		return;
	}

	notice(svs->me->nick, u->nick, nicksvs.no_nick_ownership ? _("You are now logged in as \2%s\2.") : _("You are now identified for \2%s\2."), entity(mu)->name);

	myuser_login(svs, u, mu, true);
	logcommand_user(svs, u, CMDLOG_LOGIN, "LOGIN via CERTFP (%s)", certfp);
}
