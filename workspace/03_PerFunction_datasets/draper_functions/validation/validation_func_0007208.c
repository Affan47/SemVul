irc_nick_change(session_t *s, irc_private_t *j, char *old_nick, char *new_nick)
{
	userlist_t *ulist, *newul;
	list_t i;
	userlist_t *ul;
	people_t *per;
	people_chan_t *pch;
	window_t *w;
	char *t1, *t2 = irc_uid(new_nick);

	if (!(per = irc_find_person(j->people, old_nick))) {
		debug_error("irc_nick_change() person not found?\n");
		xfree(t2);
		return 0;
	}

	for (ul=s->userlist; ul; ul = ul->next) {
		userlist_t *u = ul;
		ekg_resource_t *rl;

		for (rl = u->resources; rl; rl = rl->next) {
			ekg_resource_t *r = rl;

			if (r->priv_data != per) continue;

			xfree(r->name);
			r->name = xstrdup(t2);

			break;
		}
	}


	for (i=per->channels; i; i=i->next)
	{
		pch = (people_chan_t *)i->data;

		w = window_find_s(s, pch->chanp->name);
		if (w && (ulist = userlist_find_u(&(w->userlist), old_nick))) {
			newul = userlist_add_u(&(w->userlist), t2, new_nick);
			newul->status = ulist->status;
			userlist_remove_u(&(w->userlist), ulist);


		}
	}
	query_emit_id(NULL, USERLIST_REFRESH);


	t1 = per->nick;
	per->nick = t2;

	for (i=per->channels; i; i=i->next)
	{
		pch = (people_chan_t *)i->data;


		if (xstrlen(new_nick) > pch->chanp->longest_nick)
		{
			pch->chanp->longest_nick = xstrlen(new_nick);
			nickpad_string_create(pch->chanp);
		} else if (xstrlen(old_nick) == pch->chanp->longest_nick)
			update_longest_nick (pch->chanp);
	}

	xfree(t1);
	return 0;
}
