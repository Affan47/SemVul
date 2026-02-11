pci_ignore_hotplug(struct pci_dev *dev)
{
	struct pci_dev *bridge = dev->bus->self;

	dev->ignore_hotplug = 1;

	if (bridge)
		bridge->ignore_hotplug = 1;
}
