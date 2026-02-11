typhoon_sleep(struct typhoon *tp, pci_power_t state, __le16 events)
{
	struct pci_dev *pdev = tp->pdev;
	void __iomem *ioaddr = tp->ioaddr;
	struct cmd_desc xp_cmd;
	int err;

	INIT_COMMAND_WITH_RESPONSE(&xp_cmd, TYPHOON_CMD_ENABLE_WAKE_EVENTS);
	xp_cmd.parm1 = events;
	err = typhoon_issue_command(tp, 1, &xp_cmd, 0, NULL);
	if(err < 0) {
		netdev_err(tp->dev, "typhoon_sleep(): wake events cmd err %d\n",
			   err);
		return err;
	}

	INIT_COMMAND_NO_RESPONSE(&xp_cmd, TYPHOON_CMD_GOTO_SLEEP);
	err = typhoon_issue_command(tp, 1, &xp_cmd, 0, NULL);
	if(err < 0) {
		netdev_err(tp->dev, "typhoon_sleep(): sleep cmd err %d\n", err);
		return err;
	}

	if(typhoon_wait_status(ioaddr, TYPHOON_STATUS_SLEEPING) < 0)
		return -ETIMEDOUT;


	netif_carrier_off(tp->dev);

	pci_enable_wake(tp->pdev, state, 1);
	pci_disable_device(pdev);
	return pci_set_power_state(pdev, state);
}
