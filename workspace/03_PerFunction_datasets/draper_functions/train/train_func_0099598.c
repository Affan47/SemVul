pc_get_partner(struct map_session_data *sd)
{
	nullpo_retr(NULL, sd);

	if(!pc_ismarried(sd))
		return NULL;

	return map_charid2sd(sd->status.partner_id);
}
