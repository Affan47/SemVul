move_contact(const char *group, struct contact *c)
{
	grouplist *g = c->group;
	struct contact *con;
	LList *l = c->accounts;

	if (!strcasecmp(g->name, group))
		return;

	g->members = l_list_remove(g->members, c);
	remove_contact_line(c);
	g = find_grouplist_by_name(group);

	if (!g) {
		add_group(group);
		g = find_grouplist_by_name(group);
	}
	add_group_line(g);

	rename_nick_log(c->group->name, c->nick, group, c->nick);

	for (; l; l = l->next) {
		eb_account *ea = l->data;
		handle_group_change(ea, c->group->name, group);
	}

	con = find_contact_in_group_by_nick(c->nick, g);
	if (con && con == c) {

		return;
	} else if (con) {


		while (c && (l = c->accounts)) {
			eb_account *ea = l->data;
			c = move_account(con, ea);
		}
		return;
	} else if (!con) {
		g->members = l_list_insert_sorted(g->members, c, contact_cmp);
		c->group = g;
		add_contact_and_accounts(c);
		add_contact_line(c);
	}
}
