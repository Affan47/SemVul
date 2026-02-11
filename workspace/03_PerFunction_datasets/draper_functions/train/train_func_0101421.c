bnx2_resume(struct device *device)
{
	struct pci_dev *pdev = to_pci_dev(device);
	struct net_device *dev = pci_get_drvdata(pdev);
	struct bnx2 *bp = netdev_priv(dev);

	if (!netif_running(dev))
		return 0;

	bnx2_set_power_state(bp, PCI_D0);
	netif_device_attach(dev);
	bnx2_request_irq(bp);
	bnx2_init_nic(bp, 1);
	bnx2_netif_start(bp, true);
	return 0;
}
