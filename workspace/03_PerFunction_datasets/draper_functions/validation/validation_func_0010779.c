vnic_dev_set_ig_vlan_rewrite_mode(struct vnic_dev *vdev,
	u8 ig_vlan_rewrite_mode)
{
	u64 a0 = ig_vlan_rewrite_mode, a1 = 0;
	int wait = 1000;

	if (vnic_dev_capable(vdev, CMD_IG_VLAN_REWRITE_MODE))
		return vnic_dev_cmd(vdev, CMD_IG_VLAN_REWRITE_MODE,
				&a0, &a1, wait);
	else
		return 0;
}
