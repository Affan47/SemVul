amd_iommu_unbind_pasid(struct pci_dev *pdev, int pasid)
{
	struct pasid_state *pasid_state;
	struct device_state *dev_state;
	u16 devid;

	might_sleep();

	if (!amd_iommu_v2_supported())
		return;

	devid = device_id(pdev);
	dev_state = get_device_state(devid);
	if (dev_state == NULL)
		return;

	if (pasid < 0 || pasid >= dev_state->max_pasids)
		goto out;

	pasid_state = get_pasid_state(dev_state, pasid);
	if (pasid_state == NULL)
		goto out;


	put_pasid_state(pasid_state);


	clear_pasid_state(dev_state, pasid_state->pasid);


	mmu_notifier_unregister(&pasid_state->mn, pasid_state->mm);

	put_pasid_state_wait(pasid_state);

out:

	put_device_state(dev_state);


	put_device_state(dev_state);
}
