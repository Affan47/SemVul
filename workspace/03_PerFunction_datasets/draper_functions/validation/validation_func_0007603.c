ipwireless_interrupt(int irq, void *dev_id)
{
	struct ipw_dev *ipw = dev_id;

	if (ipw->hardware->hw_version == HW_VERSION_1)
		return ipwireless_handle_v1_interrupt(irq, ipw->hardware);
	else
		return ipwireless_handle_v2_v3_interrupt(irq, ipw->hardware);
}
