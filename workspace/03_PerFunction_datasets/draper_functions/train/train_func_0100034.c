intif_party_addmember(struct map_session_data *sd)
{
	nullpo_retv(sd);

	if (inter_fd < 0)
		return;

	WFIFOW(inter_fd, 0) = 0x3022;
	WFIFOL(inter_fd, 2) = sd->party_invite;
	WFIFOL(inter_fd, 6) = sd->status.account_id;
	WFIFOL(inter_fd,10) = sd->status.char_id;
	memcpy(WFIFOP(inter_fd,14),sd->status.name,24);
	memcpy(WFIFOP(inter_fd,38),map[sd->bl.m].name,16);
	WFIFOW(inter_fd,54) = sd->status.base_level;
	WFIFOSET(inter_fd,56);

	return;
}
