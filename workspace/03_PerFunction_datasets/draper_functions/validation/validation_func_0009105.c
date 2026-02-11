Cmd_Teamname_f(edict_t * ent)
{
	int i, u, team;
	char temp[32];

	if (!matchmode->value) {
		gi.cprintf(ent, PRINT_HIGH, "This command need matchmode to be enabled\n");
		return;
	}

	if(ctf->value) {
		gi.cprintf(ent, PRINT_HIGH, "You cant change teamnames in ctf mode\n");
		return;
	}

	if (!ent->client->resp.captain) {
		gi.cprintf(ent, PRINT_HIGH, "You need to be a captain for that\n");
		return;
	}
	team = ent->client->resp.team;
	if (teams[team].ready) {
		gi.cprintf(ent, PRINT_HIGH, "You cannot use this while 'Ready'\n");
		return;
	}
	if (team_round_going || team_game_going) {
		gi.cprintf(ent, PRINT_HIGH, "You cannot use this while playing\n");
		return;
	}
	i = gi.argc();
	if (i < 2) {
		gi.cprintf(ent, PRINT_HIGH, "Your Team Name is %s\n", teams[team].name);
		return;
	}

	Q_strncpyz(temp, gi.argv(1), sizeof(temp));
	for (u = 2; u <= i; u++) {
		Q_strncatz(temp, " ", sizeof(temp));
		Q_strncatz(temp, gi.argv(u), sizeof(temp));
	}
	temp[18] = 0;

	gi.dprintf("%s (Team %i) is now known as %s\n", teams[team].name, team, temp);
	IRC_printf(IRC_T_GAME, "%n (Team %i) is now known as %n", teams[team].name, team, temp);
	strcpy(teams[team].name, temp);
	gi.cprintf(ent, PRINT_HIGH, "New Team Name: %s\n", teams[team].name);

}
