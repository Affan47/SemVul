atcommand_charlostskill(const int fd, struct map_session_data* sd, AtCommandType command, const char* message)
{
	char character[100];
	struct map_session_data *pl_sd;
	int skill_id;

	if (!message || !*message)
		return -1;
	if (sscanf(message, "%d %99[^\n]", &skill_id, character) < 2)
		return -1;

	if ((pl_sd = map_nick2sd(character)) != NULL) {
		if (skill_get_inf2(skill_id) & INF2_QUEST && pc_checkskill2(pl_sd, skill_id) > 0) {
			pl_sd->status.skill[skill_id].lv   = 0;
			pl_sd->status.skill[skill_id].flag = 0;
			clif_skillinfoblock(pl_sd);
			msg_output(fd, msg_txt(111), pl_sd->status.name);
		}
	} else {
		clif_displaymessage(fd, msg_txt(3));
	}

	return 0;
}
