handle_surprise_event(struct slot *p_slot)
{
	u8 getstatus;

	pciehp_get_adapter_status(p_slot, &getstatus);
	if (!getstatus)
		pciehp_queue_power_work(p_slot, DISABLE_REQ);
	else
		pciehp_queue_power_work(p_slot, ENABLE_REQ);
}
