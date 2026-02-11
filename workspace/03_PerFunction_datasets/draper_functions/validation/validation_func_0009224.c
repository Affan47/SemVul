diag_ledtest_send(struct bfa_diag_s *diag, struct bfa_diag_ledtest_s *ledtest)
{
	struct bfi_diag_ledtest_req_s  *msg;

	msg = (struct bfi_diag_ledtest_req_s *)diag->ledtest.mbcmd.msg;

	bfi_h2i_set(msg->mh, BFI_MC_DIAG, BFI_DIAG_H2I_LEDTEST,
			bfa_ioc_portid(diag->ioc));


	if (ledtest->freq)
		ledtest->freq = 500 / ledtest->freq;

	if (ledtest->freq == 0)
		ledtest->freq = 1;

	bfa_trc(diag, ledtest->freq);

	msg->cmd = (u8) ledtest->cmd;
	msg->color = (u8) ledtest->color;
	msg->portid = bfa_ioc_portid(diag->ioc);
	msg->led = ledtest->led;
	msg->freq = cpu_to_be16(ledtest->freq);


	bfa_ioc_mbox_queue(diag->ioc, &diag->ledtest.mbcmd);
}
