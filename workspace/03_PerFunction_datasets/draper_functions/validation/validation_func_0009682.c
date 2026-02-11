YM2610_sh_start(const struct MachineSound *msound)
{
	int i,j;
	int rate = Machine->sample_rate;
	char buf[YM2610_NUMBUF][40];
	const char *name[YM2610_NUMBUF];
	int mixed_vol,vol[YM2610_NUMBUF];
	void *pcmbufa[YM2610_NUMBUF],*pcmbufb[YM2610_NUMBUF];
	int  pcmsizea[YM2610_NUMBUF],pcmsizeb[YM2610_NUMBUF];

	intf = msound->sound_interface;
	if( intf->num > MAX_2610 ) return 1;

	if (AY8910_sh_start(msound)) return 1;


	FMTimerInit();


	for (i = 0;i < intf->num;i++)
	{

		mixed_vol = intf->volumeFM[i];

		for (j = 0 ; j < YM2610_NUMBUF ; j++)
		{
			name[j]=buf[j];
			vol[j] = mixed_vol & 0xffff;
			mixed_vol>>=16;
			sprintf(buf[j],"%s #%d Ch%d",sound_name(msound),i,j+1);
		}
		stream[i] = stream_init_multi(YM2610_NUMBUF,name,vol,rate,i,YM2610UpdateOne);

		pcmbufa[i]  = (void *)(memory_region(intf->pcmroma[i]));
		pcmsizea[i] = memory_region_length(intf->pcmroma[i]);
		pcmbufb[i]  = (void *)(memory_region(intf->pcmromb[i]));
		pcmsizeb[i] = memory_region_length(intf->pcmromb[i]);
	}


	if (YM2610Init(intf->num,intf->baseclock,rate,
		           pcmbufa,pcmsizea,pcmbufb,pcmsizeb,
		           TimerHandler,IRQHandler) == 0)
		return 0;


	return 1;
}
