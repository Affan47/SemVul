VoiceInit()
{
	int  pk, j;
	voice_t *v;

	v = &voice_data;

	v->pitch_base = 71 << 12;
	v->pitch_range =  0x1000;

	for(pk=0; pk<N_PEAKS+1; pk++)
	{
	for(j=0; j<3; j++)
		voice_pcnt[pk][j] = 100;
	}
	VoiceSetup();

	voice = v;
}
