bfa_nw_ioc_mbox_isr(struct bfa_ioc *ioc)
{
	struct bfa_ioc_mbox_mod *mod = &ioc->mbox_mod;
	struct bfi_mbmsg m;
	int				mc;

	if (bfa_ioc_msgget(ioc, &m)) {


		mc = m.mh.msg_class;
		if (mc == BFI_MC_IOC) {
			bfa_ioc_isr(ioc, &m);
			return;
		}

		if ((mc >= BFI_MC_MAX) || (mod->mbhdlr[mc].cbfn == NULL))
			return;

		mod->mbhdlr[mc].cbfn(mod->mbhdlr[mc].cbarg, &m);
	}

	bfa_ioc_lpu_read_stat(ioc);


	bfa_ioc_mbox_poll(ioc);
}
