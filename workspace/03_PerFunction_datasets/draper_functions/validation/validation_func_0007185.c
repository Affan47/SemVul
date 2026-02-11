i5400_probe1(struct pci_dev *pdev, int dev_idx)
{
	struct mem_ctl_info *mci;
	struct i5400_pvt *pvt;
	struct edac_mc_layer layers[3];

	if (dev_idx >= ARRAY_SIZE(i5400_devs))
		return -EINVAL;

	edac_dbg(0, "MC: pdev bus %u dev=0x%x fn=0x%x\n",
		 pdev->bus->number,
		 PCI_SLOT(pdev->devfn), PCI_FUNC(pdev->devfn));


	if (PCI_FUNC(pdev->devfn) != 0)
		return -ENODEV;


	layers[0].type = EDAC_MC_LAYER_BRANCH;
	layers[0].size = MAX_BRANCHES;
	layers[0].is_virt_csrow = false;
	layers[1].type = EDAC_MC_LAYER_CHANNEL;
	layers[1].size = CHANNELS_PER_BRANCH;
	layers[1].is_virt_csrow = false;
	layers[2].type = EDAC_MC_LAYER_SLOT;
	layers[2].size = DIMMS_PER_CHANNEL;
	layers[2].is_virt_csrow = true;
	mci = edac_mc_alloc(0, ARRAY_SIZE(layers), layers, sizeof(*pvt));
	if (mci == NULL)
		return -ENOMEM;

	edac_dbg(0, "MC: mci = %p\n", mci);

	mci->pdev = &pdev->dev;

	pvt = mci->pvt_info;
	pvt->system_address = pdev;
	pvt->maxch = MAX_CHANNELS;
	pvt->maxdimmperch = DIMMS_PER_CHANNEL;


	if (i5400_get_devices(mci, dev_idx))
		goto fail0;


	i5400_get_mc_regs(mci);

	mci->mc_idx = 0;
	mci->mtype_cap = MEM_FLAG_FB_DDR2;
	mci->edac_ctl_cap = EDAC_FLAG_NONE;
	mci->edac_cap = EDAC_FLAG_NONE;
	mci->mod_name = "i5400_edac.c";
	mci->mod_ver = I5400_REVISION;
	mci->ctl_name = i5400_devs[dev_idx].ctl_name;
	mci->dev_name = pci_name(pdev);
	mci->ctl_page_to_phys = NULL;


	mci->edac_check = i5400_check_error;


	if (i5400_init_dimms(mci)) {
		edac_dbg(0, "MC: Setting mci->edac_cap to EDAC_FLAG_NONE because i5400_init_dimms() returned nonzero value\n");
		mci->edac_cap = EDAC_FLAG_NONE;
	} else {
		edac_dbg(1, "MC: Enable error reporting now\n");
		i5400_enable_error_reporting(mci);
	}


	if (edac_mc_add_mc(mci)) {
		edac_dbg(0, "MC: failed edac_mc_add_mc()\n");


		goto fail1;
	}

	i5400_clear_error(mci);


	i5400_pci = edac_pci_create_generic_ctl(&pdev->dev, EDAC_MOD_STR);
	if (!i5400_pci) {
		printk(KERN_WARNING
			"%s(): Unable to create PCI control\n",
			__func__);
		printk(KERN_WARNING
			"%s(): PCI error report via EDAC not setup\n",
			__func__);
	}

	return 0;


fail1:

	i5400_put_devices(mci);

fail0:
	edac_mc_free(mci);
	return -ENODEV;
}
