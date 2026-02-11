atcommand_doom(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	struct map_session_data *pl_sd;
	int i;

	nullpo_retr(-1, sd);

	for (i = 0; i < fd_max; i++) {
		if (session[i] && (pl_sd = (struct map_session_data *)session[i]->session_data) &&
		    pl_sd->state.auth && pc_isGM(sd) >= pc_isGM(pl_sd))
		{
			if (command == AtCommand_DoomMap && sd->bl.m != pl_sd->bl.m)
				continue;

			pc_damage(NULL, pl_sd, pl_sd->status.hp + 1);
			clif_displaymessage(pl_sd->fd, msg_txt(61));
		}
	}

	return 0;
}
