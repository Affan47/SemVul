fix_master_sid(int a_id)
{
	int i;
	adapter *ad;
	streams *sid;
	ad = get_adapter(a_id);

	if (!ad || ad->master_sid != -1)
		return 0;
	if (ad->sid_cnt < 1)
		return 0;
	for (i = 0; i < MAX_STREAMS; i++)
		if ((sid = get_sid_for(i)) && sid->adapter == a_id)
		{
			LOG("fix master_sid to %d for adapter %d", sid->sid, a_id);
			ad->master_sid = i;
		}
	return 0;
}
