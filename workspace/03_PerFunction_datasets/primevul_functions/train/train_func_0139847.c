static void bnx2x_shutdown(struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata(pdev);
	struct bnx2x *bp;

	if (!dev)
		return;

	bp = netdev_priv(dev);
	if (!bp)
		return;

	rtnl_lock();
	netif_device_detach(dev);
	rtnl_unlock();


	__bnx2x_remove(pdev, dev, bp, false);
}
