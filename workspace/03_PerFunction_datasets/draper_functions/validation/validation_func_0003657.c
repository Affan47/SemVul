brcmf_fws_hanger_init(struct brcmf_fws_hanger *hanger)
{
	int i;

	memset(hanger, 0, sizeof(*hanger));
	for (i = 0; i < ARRAY_SIZE(hanger->items); i++)
		hanger->items[i].state = BRCMF_FWS_HANGER_ITEM_STATE_FREE;
}
