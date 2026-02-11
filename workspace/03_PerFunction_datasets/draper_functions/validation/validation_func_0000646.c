amd_ntb_link_is_up(struct ntb_dev *ntb,
			      enum ntb_speed *speed,
			      enum ntb_width *width)
{
	struct amd_ntb_dev *ndev = ntb_ndev(ntb);
	int ret = 0;

	if (amd_link_is_up(ndev)) {
		if (speed)
			*speed = NTB_LNK_STA_SPEED(ndev->lnk_sta);
		if (width)
			*width = NTB_LNK_STA_WIDTH(ndev->lnk_sta);

		dev_dbg(ndev_dev(ndev), "link is up.\n");

		ret = 1;
	} else {
		if (speed)
			*speed = NTB_SPEED_NONE;
		if (width)
			*width = NTB_WIDTH_NONE;

		dev_dbg(ndev_dev(ndev), "link is down.\n");
	}

	return ret;
}
