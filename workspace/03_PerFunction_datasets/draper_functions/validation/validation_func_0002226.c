pci_generic_config_read(struct pci_bus *bus, unsigned int devfn,
			    int where, int size, u32 *val)
{
	void __iomem *addr;

	addr = bus->ops->map_bus(bus, devfn, where);
	if (!addr) {
		*val = ~0;
		return PCIBIOS_DEVICE_NOT_FOUND;
	}

	if (size == 1)
		*val = readb(addr);
	else if (size == 2)
		*val = readw(addr);
	else
		*val = readl(addr);

	return PCIBIOS_SUCCESSFUL;
}
