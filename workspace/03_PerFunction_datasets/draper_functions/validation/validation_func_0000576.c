cx24110_get_frontend(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;
	struct cx24110_state *state = fe->demodulator_priv;
	s32 afc; unsigned sclk;


	sclk = cx24110_readreg (state, 0x07) & 0x03;


	if (sclk==0) sclk=90999000L/2L;
	else if (sclk==1) sclk=60666000L;
	else if (sclk==2) sclk=80888000L;
	else sclk=90999000L;
	sclk>>=8;
	afc = sclk*(cx24110_readreg (state, 0x44)&0x1f)+
	      ((sclk*cx24110_readreg (state, 0x45))>>8)+
	      ((sclk*cx24110_readreg (state, 0x46))>>16);

	p->frequency += afc;
	p->inversion = (cx24110_readreg (state, 0x22) & 0x10) ?
				INVERSION_ON : INVERSION_OFF;
	p->fec_inner = cx24110_get_fec(state);

	return 0;
}
