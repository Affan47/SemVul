ValidateSelectedItem (edict_t * ent)
{
	gclient_t *cl;

	cl = ent->client;

	if (cl->pers.inventory[cl->pers.selected_item])
		return;

	SelectNextItem (ent, -1);
}
