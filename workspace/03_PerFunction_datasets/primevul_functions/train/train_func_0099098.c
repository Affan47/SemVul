getspec(struct tbl *vp)
{
	mksh_ari_u num;
	int st;
	struct timeval tv;

	switch ((st = special(vp->name))) {
	case V_COLUMNS:
	case V_LINES:


		if (got_winch)
			change_winsz();
		break;
	}
	switch (st) {
	case V_BASHPID:
		num.u = (mksh_uari_t)procpid;
		break;
	case V_COLUMNS:
		num.i = x_cols;
		break;
	case V_HISTSIZE:
		num.i = histsize;
		break;
	case V_LINENO:
		num.i = current_lineno + user_lineno;
		break;
	case V_LINES:
		num.i = x_lins;
		break;
	case V_EPOCHREALTIME: {

		char buf[18];

		vp->flag &= ~SPECIAL;
		mksh_TIME(tv);
		shf_snprintf(buf, sizeof(buf), "%u.%06u",
		    (unsigned)tv.tv_sec, (unsigned)tv.tv_usec);
		setstr(vp, buf, KSH_RETURN_ERROR | 0x4);
		vp->flag |= SPECIAL;
		return;
	}
	case V_OPTIND:
		num.i = user_opt.uoptind;
		break;
	case V_RANDOM:
		num.i = rndget();
		break;
	case V_SECONDS:


		if (vp->flag & ISSET) {
			mksh_TIME(tv);
			num.i = tv.tv_sec - seconds;
		} else
			return;
		break;
	default:

		return;
	}
	vp->flag &= ~SPECIAL;
	setint_n(vp, num.i, 0);
	vp->flag |= SPECIAL;
}
