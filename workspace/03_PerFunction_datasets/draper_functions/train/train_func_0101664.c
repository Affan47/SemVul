l3dss1_progress(struct l3_process *pc, u_char pr, void *arg)
{
	struct sk_buff *skb = arg;
	int err = 0;
	u_char *p;

	if ((p = findie(skb->data, skb->len, IE_PROGRESS, 0))) {
		if (p[1] != 2) {
			err = 1;
			pc->para.cause = 100;
		} else if (!(p[2] & 0x70)) {
			switch (p[2]) {
			case 0x80:
			case 0x81:
			case 0x82:
			case 0x84:
			case 0x85:
			case 0x87:
			case 0x8a:
				switch (p[3]) {
				case 0x81:
				case 0x82:
				case 0x83:
				case 0x84:
				case 0x88:
					break;
				default:
					err = 2;
					pc->para.cause = 100;
					break;
				}
				break;
			default:
				err = 3;
				pc->para.cause = 100;
				break;
			}
		}
	} else {
		pc->para.cause = 96;
		err = 4;
	}
	if (err) {
		if (pc->debug & L3_DEB_WARN)
			l3_debug(pc->st, "progress error %d", err);
		l3dss1_status_send(pc, pr, NULL);
		return;
	}

	err = check_infoelements(pc, skb, ie_PROGRESS);
	if (err)
		l3dss1_std_ie_err(pc, err);
	if (ERR_IE_COMPREHENSION != err)
		pc->st->l3.l3l4(pc->st, CC_PROGRESS | INDICATION, pc);
}
