FMsave_state_adpcma(const char *name,int num,ADPCM_CH *adpcm)
{
	int ch;
	char state_name[20];

	for(ch=0;ch<6;ch++,adpcm++)
	{
		sprintf(state_name,"%s.CH%d",name,ch);

		state_save_register_UINT8 (state_name, num, "flag"    , &adpcm->flag      , 1);
		state_save_register_UINT8 (state_name, num, "data"    , &adpcm->now_data  , 1);
		state_save_register_UINT32(state_name, num, "addr"    , &adpcm->now_addr  , 1);
		state_save_register_UINT32(state_name, num, "step"    , &adpcm->now_step  , 1);
		state_save_register_INT32 (state_name, num, "a_acc"   , &adpcm->adpcm_acc , 1);
		state_save_register_INT32 (state_name, num, "a_step"  , &adpcm->adpcm_step, 1);
		state_save_register_INT32 (state_name, num, "a_out"   , &adpcm->adpcm_out , 1);
	}
}
