static void skfp_ctl_set_multicast_list_wo_lock(struct net_device *dev)
{
	struct s_smc *smc = netdev_priv(dev);
	struct dev_mc_list *dmi;
	int i;


	if (dev->flags & IFF_PROMISC) {
		mac_drv_rx_mode(smc, RX_ENABLE_PROMISC);
		PRINTK(KERN_INFO "PROMISCUOUS MODE ENABLED\n");
	}

	else {
		mac_drv_rx_mode(smc, RX_DISABLE_PROMISC);
		PRINTK(KERN_INFO "PROMISCUOUS MODE DISABLED\n");


		mac_clear_multicast(smc);
		mac_drv_rx_mode(smc, RX_DISABLE_ALLMULTI);

		if (dev->flags & IFF_ALLMULTI) {
			mac_drv_rx_mode(smc, RX_ENABLE_ALLMULTI);
			PRINTK(KERN_INFO "ENABLE ALL MC ADDRESSES\n");
		} else if (dev->mc_count > 0) {
			if (dev->mc_count <= FPMAX_MULTICAST) {


				dmi = dev->mc_list;

				for (i = 0; i < dev->mc_count; i++) {
					mac_add_multicast(smc,
							  (struct fddi_addr *)dmi->dmi_addr,
							  1);

					PRINTK(KERN_INFO "ENABLE MC ADDRESS:");
					PRINTK(" %02x %02x %02x ",
					       dmi->dmi_addr[0],
					       dmi->dmi_addr[1],
					       dmi->dmi_addr[2]);
					PRINTK("%02x %02x %02x\n",
					       dmi->dmi_addr[3],
					       dmi->dmi_addr[4],
					       dmi->dmi_addr[5]);
					dmi = dmi->next;
				}

			} else {

				mac_drv_rx_mode(smc, RX_ENABLE_ALLMULTI);
				PRINTK(KERN_INFO "ENABLE ALL MC ADDRESSES\n");
			}
		} else {

			PRINTK(KERN_INFO "DISABLE ALL MC ADDRESSES\n");
		}


		mac_update_multicast(smc);
	}
	return;
}
