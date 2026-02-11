WILC_WFI_mgmt_rx(struct wilc *wilc, u8 *buff, u32 size)
{
	int i = 0;
	perInterface_wlan_t *nic;


	for (i = 0; i < wilc->vif_num; i++) {
		nic = netdev_priv(wilc->vif[i].ndev);
		if (nic->monitor_flag) {
			WILC_WFI_monitor_rx(buff, size);
			return;
		}
	}

	nic = netdev_priv(wilc->vif[1].ndev);
	if ((buff[0] == nic->g_struct_frame_reg[0].frame_type && nic->g_struct_frame_reg[0].reg) ||
	    (buff[0] == nic->g_struct_frame_reg[1].frame_type && nic->g_struct_frame_reg[1].reg))
		WILC_WFI_p2p_rx(wilc->vif[1].ndev, buff, size);
}
