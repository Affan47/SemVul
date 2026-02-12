static void __bnx2x_remove(struct pci_dev *pdev,
			   struct net_device *dev,
			   struct bnx2x *bp,
			   bool remove_netdev)
{
	if (bp->ptp_clock) {
		ptp_clock_unregister(bp->ptp_clock);
		bp->ptp_clock = NULL;
	}


	if (!NO_FCOE(bp)) {
		rtnl_lock();
		dev_addr_del(bp->dev, bp->fip_mac, NETDEV_HW_ADDR_T_SAN);
		rtnl_unlock();
	}

#ifdef BCM_DCBNL

	bnx2x_dcbnl_update_applist(bp, true);
#endif

	if (IS_PF(bp) &&
	    !BP_NOMCP(bp) &&
	    (bp->flags & BC_SUPPORTS_RMMOD_CMD))
		bnx2x_fw_command(bp, DRV_MSG_CODE_RMMOD, 0);


	if (remove_netdev) {
		unregister_netdev(dev);
	} else {
		rtnl_lock();
		dev_close(dev);
		rtnl_unlock();
	}

	bnx2x_iov_remove_one(bp);


	if (IS_PF(bp)) {
		bnx2x_set_power_state(bp, PCI_D0);
		bnx2x_set_os_driver_state(bp, OS_DRIVER_STATE_NOT_LOADED);


		bnx2x_reset_endianity(bp);
	}


	bnx2x_disable_msi(bp);


	if (IS_PF(bp))
		bnx2x_set_power_state(bp, PCI_D3hot);


	cancel_delayed_work_sync(&bp->sp_rtnl_task);


	if (IS_VF(bp))
		bnx2x_vfpf_release(bp);


	if (system_state == SYSTEM_POWER_OFF) {
		pci_wake_from_d3(pdev, bp->wol);
		pci_set_power_state(pdev, PCI_D3hot);
	}

	bnx2x_disable_pcie_error_reporting(bp);
	if (remove_netdev) {
		if (bp->regview)
			iounmap(bp->regview);


		if (IS_PF(bp)) {
			if (bp->doorbells)
				iounmap(bp->doorbells);

			bnx2x_release_firmware(bp);
		} else {
			bnx2x_vf_pci_dealloc(bp);
		}
		bnx2x_free_mem_bp(bp);

		free_netdev(dev);

		if (atomic_read(&pdev->enable_cnt) == 1)
			pci_release_regions(pdev);

		pci_disable_device(pdev);
	}
}
