prism54_remove(struct pci_dev *pdev)
{
	struct net_device *ndev = pci_get_drvdata(pdev);
	islpci_private *priv = ndev ? netdev_priv(ndev) : NULL;
	BUG_ON(!priv);

	if (!__in_cleanup_module) {
		printk(KERN_DEBUG "%s: hot unplug detected\n", ndev->name);
		islpci_set_state(priv, PRV_STATE_OFF);
	}

	printk(KERN_DEBUG "%s: removing device\n", ndev->name);

	unregister_netdev(ndev);


	if (islpci_get_state(priv) != PRV_STATE_OFF) {
		isl38xx_disable_interrupts(priv->device_base);
		islpci_set_state(priv, PRV_STATE_OFF);


	}

	free_irq(pdev->irq, priv);


	islpci_free_memory(priv);

	free_netdev(ndev);
	priv = NULL;

	pci_clear_mwi(pdev);

	pci_release_regions(pdev);

	pci_disable_device(pdev);
}
