static int skfp_open(struct net_device *dev)
{
	struct s_smc *smc = netdev_priv(dev);
	int err;

	PRINTK(KERN_INFO "entering skfp_open\n");

	err = request_irq(dev->irq, skfp_interrupt, IRQF_SHARED,
			  dev->name, dev);
	if (err)
		return err;


	read_address(smc, NULL);
	memcpy(dev->dev_addr, smc->hw.fddi_canon_addr.a, 6);

	init_smt(smc, NULL);
	smt_online(smc, 1);
	STI_FBI();


	mac_clear_multicast(smc);


	mac_drv_rx_mode(smc, RX_DISABLE_PROMISC);

	netif_start_queue(dev);
	return (0);
}
