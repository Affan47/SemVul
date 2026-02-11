prism2_config(struct pcmcia_device *link)
{
	struct net_device *dev;
	struct hostap_interface *iface;
	local_info_t *local;
	int ret = 1;
	struct hostap_cs_priv *hw_priv;
	unsigned long flags;

	PDEBUG(DEBUG_FLOW, "prism2_config()\n");

	hw_priv = kzalloc(sizeof(*hw_priv), GFP_KERNEL);
	if (hw_priv == NULL) {
		ret = -ENOMEM;
		goto failed;
	}


	link->config_flags |= CONF_AUTO_SET_VPP | CONF_AUTO_AUDIO |
		CONF_AUTO_CHECK_VCC | CONF_AUTO_SET_IO | CONF_ENABLE_IRQ;
	if (ignore_cis_vcc)
		link->config_flags &= ~CONF_AUTO_CHECK_VCC;
	ret = pcmcia_loop_config(link, prism2_config_check, NULL);
	if (ret) {
		if (!ignore_cis_vcc)
			printk(KERN_ERR "GetNextTuple(): No matching "
			       "CIS configuration.  Maybe you need the "
			       "ignore_cis_vcc=1 parameter.\n");
		goto failed;
	}


	dev = prism2_init_local_data(&prism2_pccard_funcs, 0,
				     &link->dev);
	if (dev == NULL)
		goto failed;
	link->priv = dev;

	iface = netdev_priv(dev);
	local = iface->local;
	local->hw_priv = hw_priv;
	hw_priv->link = link;


	ret = pcmcia_request_irq(link, prism2_interrupt);
	if (ret)
		goto failed;

	ret = pcmcia_enable_device(link);
	if (ret)
		goto failed;

	spin_lock_irqsave(&local->irq_init_lock, flags);
	dev->irq = link->irq;
	dev->base_addr = link->resource[0]->start;
	spin_unlock_irqrestore(&local->irq_init_lock, flags);

	local->shutdown = 0;

	sandisk_enable_wireless(dev);

	ret = prism2_hw_config(dev, 1);
	if (!ret)
		ret = hostap_hw_ready(dev);

	return ret;

 failed:
	kfree(hw_priv);
	prism2_release((u_long)link);
	return ret;
}
