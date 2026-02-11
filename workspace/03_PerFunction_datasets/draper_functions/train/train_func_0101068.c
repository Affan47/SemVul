audio_group_open(void)
{
	int i;
	if(_is_open)
		return;

	memset(grouptab, 0, sizeof(grouptab));
	for(i = 0; i < AUDIO_MAX_GROUPS; ++i)
		acc_copya(&grouptab[i].ctl, &a_group_def_ctl);
	_is_open = 1;
}
