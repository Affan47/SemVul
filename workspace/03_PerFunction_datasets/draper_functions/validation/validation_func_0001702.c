typhoon_resume(struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata(pdev);
	struct typhoon *tp = netdev_priv(dev);


	if(!netif_running(dev))
		return 0;

	if(typhoon_wakeup(tp, WaitNoSleep) < 0) {
		netdev_err(dev, "critical: could not wake up in resume\n");
		goto reset;
	}

	if(typhoon_start_runtime(tp) < 0) {
		netdev_err(dev, "critical: could not start runtime in resume\n");
		goto reset;
	}

	netif_device_attach(dev);
	return 0;

reset:
	typhoon_reset(tp->ioaddr, NoWait);
	return -EBUSY;
}
