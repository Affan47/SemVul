static void set_global_def(void)
{
	struct VOICE_S *p_voice;
	int i;

	for (i = MAXVOICE, p_voice = voice_tb;
	     --i >= 0;
	     p_voice++) {
		switch (p_voice->key.instr) {
		case 0:
			if (!pipeformat) {

				break;
			}

		case K_HP:
		case K_Hp:
			if (p_voice->posit.std == 0)
				p_voice->posit.std = SL_BELOW;
			break;
		}


		if (!cfmt.autoclef
		 && p_voice->s_clef
		 && (p_voice->s_clef->sflags & S_CLEF_AUTO)) {
			p_voice->s_clef->u.clef.type = TREBLE;
			p_voice->s_clef->sflags &= ~S_CLEF_AUTO;
		}
	}


	curvoice = &voice_tb[parsys->top_voice];
}
