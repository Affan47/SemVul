pci_seq_stop(struct seq_file *m, void *v)
{
	if (v) {
		struct pci_dev *dev = v;
		pci_dev_put(dev);
	}
}
