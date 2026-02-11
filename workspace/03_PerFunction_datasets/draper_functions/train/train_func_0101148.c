i7core_remove(struct pci_dev *pdev)
{
	struct i7core_dev *i7core_dev;

	edac_dbg(0, "\n");


	mutex_lock(&i7core_edac_lock);

	if (unlikely(!probed)) {
		mutex_unlock(&i7core_edac_lock);
		return;
	}

	list_for_each_entry(i7core_dev, &i7core_edac_list, list)
		i7core_unregister_mci(i7core_dev);


	i7core_put_all_devices();

	probed--;

	mutex_unlock(&i7core_edac_lock);
}
