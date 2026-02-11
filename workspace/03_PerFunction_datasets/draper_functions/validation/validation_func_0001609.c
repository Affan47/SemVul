lgdt3305_rfagc_loop(struct lgdt3305_state *state,
			       struct dtv_frontend_properties *p)
{
	u16 ifbw, rfbw, agcdelay;

	switch (p->modulation) {
	case VSB_8:
		agcdelay = 0x04c0;
		rfbw     = 0x8000;
		ifbw     = 0x8000;
		break;
	case QAM_64:
	case QAM_256:
		agcdelay = 0x046b;
		rfbw     = 0x8889;


		if (state->cfg->demod_chip == LGDT3304)
			ifbw = 0x6666;
		else
			ifbw = 0x8888;
		break;
	default:
		return -EINVAL;
	}

	if (state->cfg->rf_agc_loop) {
		lg_dbg("agcdelay: 0x%04x, rfbw: 0x%04x\n", agcdelay, rfbw);


		lgdt3305_write_reg(state, LGDT3305_AGC_DELAY_PT_1,
				   agcdelay >> 8);
		lgdt3305_write_reg(state, LGDT3305_AGC_DELAY_PT_2,
				   agcdelay & 0xff);

		lgdt3305_write_reg(state, LGDT3305_RFAGC_LOOP_FLTR_BW_1,
				   rfbw >> 8);
		lgdt3305_write_reg(state, LGDT3305_RFAGC_LOOP_FLTR_BW_2,
				   rfbw & 0xff);
	} else {
		lg_dbg("ifbw: 0x%04x\n", ifbw);


		lgdt3305_write_reg(state, LGDT3305_IFBW_1, ifbw >> 8);
		lgdt3305_write_reg(state, LGDT3305_IFBW_2, ifbw & 0xff);
	}

	return 0;
}
