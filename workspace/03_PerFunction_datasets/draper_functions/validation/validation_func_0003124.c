liquidio_link_ctrl_cmd_completion(void *nctrl_ptr)
{
	struct octnic_ctrl_pkt *nctrl = (struct octnic_ctrl_pkt *)nctrl_ptr;
	struct net_device *netdev = (struct net_device *)nctrl->netpndev;
	struct lio *lio = GET_LIO(netdev);
	struct octeon_device *oct = lio->oct_dev;

	switch (nctrl->ncmd.s.cmd) {
	case OCTNET_CMD_CHANGE_DEVFLAGS:
	case OCTNET_CMD_SET_MULTI_LIST:
		break;

	case OCTNET_CMD_CHANGE_MACADDR:

		netif_info(lio, probe, lio->netdev, " MACAddr changed to 0x%llx\n",
			   CVM_CAST64(nctrl->udd[0]));
		dev_info(&oct->pci_dev->dev, "%s MACAddr changed to 0x%llx\n",
			 netdev->name, CVM_CAST64(nctrl->udd[0]));
		memcpy(netdev->dev_addr, ((u8 *)&nctrl->udd[0]) + 2, ETH_ALEN);
		break;

	case OCTNET_CMD_CHANGE_MTU:

		netif_info(lio, probe, lio->netdev, " MTU Changed from %d to %d\n",
			   netdev->mtu, nctrl->ncmd.s.param2);
		dev_info(&oct->pci_dev->dev, "%s MTU Changed from %d to %d\n",
			 netdev->name, netdev->mtu,
			 nctrl->ncmd.s.param2);
		netdev->mtu = nctrl->ncmd.s.param2;
		break;

	case OCTNET_CMD_GPIO_ACCESS:
		netif_info(lio, probe, lio->netdev, "LED Flashing visual identification\n");

		break;

	case OCTNET_CMD_LRO_ENABLE:
		dev_info(&oct->pci_dev->dev, "%s LRO Enabled\n", netdev->name);
		break;

	case OCTNET_CMD_LRO_DISABLE:
		dev_info(&oct->pci_dev->dev, "%s LRO Disabled\n",
			 netdev->name);
		break;

	case OCTNET_CMD_VERBOSE_ENABLE:
		dev_info(&oct->pci_dev->dev, "%s LRO Enabled\n", netdev->name);
		break;

	case OCTNET_CMD_VERBOSE_DISABLE:
		dev_info(&oct->pci_dev->dev, "%s LRO Disabled\n",
			 netdev->name);
		break;

	case OCTNET_CMD_SET_SETTINGS:
		dev_info(&oct->pci_dev->dev, "%s settings changed\n",
			 netdev->name);

		break;

	default:
		dev_err(&oct->pci_dev->dev, "%s Unknown cmd %d\n", __func__,
			nctrl->ncmd.s.cmd);
	}
}
