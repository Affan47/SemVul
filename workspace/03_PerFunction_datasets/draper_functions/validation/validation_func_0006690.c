vlsi_irda_resume(struct pci_dev *pdev)
{
	struct net_device *ndev = pci_get_drvdata(pdev);
	vlsi_irda_dev_t	*idev;

	if (!ndev) {
		net_err_ratelimited("%s - %s: no netdevice\n",
				    __func__, pci_name(pdev));
		return 0;
	}
	idev = netdev_priv(ndev);
	mutex_lock(&idev->mtx);
	if (pdev->current_state == 0) {
		mutex_unlock(&idev->mtx);
		net_warn_ratelimited("%s - %s: already resumed\n",
				     __func__, pci_name(pdev));
		return 0;
	}

	pci_set_power_state(pdev, PCI_D0);
	pdev->current_state = PM_EVENT_ON;

	if (!idev->resume_ok) {


		net_warn_ratelimited("%s - hm, nothing to resume?\n", __func__);
		mutex_unlock(&idev->mtx);
		return 0;
	}

	if (netif_running(ndev)) {
		pci_restore_state(pdev);
		vlsi_start_hw(idev);
		netif_device_attach(ndev);
	}
	idev->resume_ok = 0;
	mutex_unlock(&idev->mtx);
	return 0;
}
