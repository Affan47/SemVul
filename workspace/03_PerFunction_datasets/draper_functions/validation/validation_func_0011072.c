vfio_direct_config_read(struct vfio_pci_device *vdev, int pos,
				   int count, struct perm_bits *perm,
				   int offset, __le32 *val)
{
	int ret;

	ret = vfio_user_config_read(vdev->pdev, pos, val, count);
	if (ret)
		return pcibios_err_to_errno(ret);

	if (pos >= PCI_CFG_SPACE_SIZE) {
		if (offset < 4)
			memcpy(val, vdev->vconfig + pos, count);
	} else if (pos >= PCI_STD_HEADER_SIZEOF) {
		if (offset == PCI_CAP_LIST_ID && count > 1)
			memcpy(val, vdev->vconfig + pos,
			       min(PCI_CAP_FLAGS, count));
		else if (offset == PCI_CAP_LIST_NEXT)
			memcpy(val, vdev->vconfig + pos, 1);
	}

	return count;
}
