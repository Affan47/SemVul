modem_dialout_exit(struct cpssp *cpssp)
{

	if (cpssp->dialout.state == STATE_ONLINE) {
		modem_phone_send_ctrl(cpssp, SIG_TELE_HANGUP);
	}
}
