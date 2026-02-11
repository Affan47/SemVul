dib0090_identify(struct dvb_frontend *fe)
{
	struct dib0090_state *state = fe->tuner_priv;
	u16 v;
	struct dib0090_identity *identity = &state->identity;

	v = dib0090_read_reg(state, 0x1a);

	identity->p1g = 0;
	identity->in_soc = 0;

	dprintk("Tuner identification (Version = 0x%04x)", v);


	v &= ~KROSUS_PLL_LOCKED;

	identity->version = v & 0xff;
	identity->product = (v >> 8) & 0xf;

	if (identity->product != KROSUS)
		goto identification_error;

	if ((identity->version & 0x3) == SOC) {
		identity->in_soc = 1;
		switch (identity->version) {
		case SOC_8090_P1G_11R1:
			dprintk("SOC 8090 P1-G11R1 Has been detected");
			identity->p1g = 1;
			break;
		case SOC_8090_P1G_21R1:
			dprintk("SOC 8090 P1-G21R1 Has been detected");
			identity->p1g = 1;
			break;
		case SOC_7090_P1G_11R1:
			dprintk("SOC 7090 P1-G11R1 Has been detected");
			identity->p1g = 1;
			break;
		case SOC_7090_P1G_21R1:
			dprintk("SOC 7090 P1-G21R1 Has been detected");
			identity->p1g = 1;
			break;
		default:
			goto identification_error;
		}
	} else {
		switch ((identity->version >> 5) & 0x7) {
		case MP001:
			dprintk("MP001 : 9090/8096");
			break;
		case MP005:
			dprintk("MP005 : Single Sband");
			break;
		case MP008:
			dprintk("MP008 : diversity VHF-UHF-LBAND");
			break;
		case MP009:
			dprintk("MP009 : diversity 29098 CBAND-UHF-LBAND-SBAND");
			break;
		default:
			goto identification_error;
		}

		switch (identity->version & 0x1f) {
		case P1G_21R2:
			dprintk("P1G_21R2 detected");
			identity->p1g = 1;
			break;
		case P1G:
			dprintk("P1G detected");
			identity->p1g = 1;
			break;
		case P1D_E_F:
			dprintk("P1D/E/F detected");
			break;
		case P1C:
			dprintk("P1C detected");
			break;
		case P1A_B:
			dprintk("P1-A/B detected: driver is deactivated - not available");
			goto identification_error;
			break;
		default:
			goto identification_error;
		}
	}

	return 0;

identification_error:
	return -EIO;
}
