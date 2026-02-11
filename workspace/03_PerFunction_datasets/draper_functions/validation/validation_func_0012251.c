mgslpc_config(struct pcmcia_device *link)
{
	MGSLPC_INFO *info = link->priv;
	int ret;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("mgslpc_config(0x%p)\n", link);

	link->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_IO;

	ret = pcmcia_loop_config(link, mgslpc_ioprobe, NULL);
	if (ret != 0)
		goto failed;

	link->config_index = 8;
	link->config_regs = PRESENT_OPTION;

	ret = pcmcia_request_irq(link, mgslpc_isr);
	if (ret)
		goto failed;
	ret = pcmcia_enable_device(link);
	if (ret)
		goto failed;

	info->io_base = link->resource[0]->start;
	info->irq_level = link->irq;
	return 0;

failed:
	mgslpc_release((u_long)link);
	return -ENODEV;
}
