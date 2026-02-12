pci_emul_free_bars(struct pci_vdev *pdi)
{
	int i, enabled;

	for (i = 0; i < PCI_BARMAX; i++) {
		if ((pdi->bar[i].type != PCIBAR_NONE) &&
			(pdi->bar[i].type != PCIBAR_MEMHI64)){


			if (pdi->bar[i].type == PCIBAR_IO)
				enabled = porten(pdi);
			else
				enabled = memen(pdi);

			if (enabled)
				unregister_bar(pdi, i);
			pdi->bar[i].type = PCIBAR_NONE;
		}
	}
}
