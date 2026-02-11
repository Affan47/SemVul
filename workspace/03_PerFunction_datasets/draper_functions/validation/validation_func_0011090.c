get_logical_state(struct hfi1_pportdata *ppd)
{
	u32 new_state;

	new_state = chip_to_opa_lstate(ppd->dd, read_logical_state(ppd->dd));
	if (new_state != ppd->lstate) {
		dd_dev_info(ppd->dd, "logical state changed to %s (0x%x)\n",
			opa_lstate_name(new_state), new_state);
		ppd->lstate = new_state;
	}


	if (ppd->statusp) {
		switch (ppd->lstate) {
		case IB_PORT_DOWN:
		case IB_PORT_INIT:
			*ppd->statusp &= ~(HFI1_STATUS_IB_CONF |
					   HFI1_STATUS_IB_READY);
			break;
		case IB_PORT_ARMED:
			*ppd->statusp |= HFI1_STATUS_IB_CONF;
			break;
		case IB_PORT_ACTIVE:
			*ppd->statusp |= HFI1_STATUS_IB_READY;
			break;
		}
	}
	return ppd->lstate;
}
