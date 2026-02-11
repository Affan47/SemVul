pci_read_aer(struct pci_bus *bus, unsigned int devfn, int where,
			int size, u32 *val)
{
	u32 *sim;
	struct aer_error *err;
	unsigned long flags;
	struct pci_ops *ops;
	int domain;

	spin_lock_irqsave(&inject_lock, flags);
	if (size != sizeof(u32))
		goto out;
	domain = pci_domain_nr(bus);
	if (domain < 0)
		goto out;
	err = __find_aer_error((u16)domain, bus->number, devfn);
	if (!err)
		goto out;

	sim = find_pci_config_dword(err, where, NULL);
	if (sim) {
		*val = *sim;
		spin_unlock_irqrestore(&inject_lock, flags);
		return 0;
	}
out:
	ops = __find_pci_bus_ops(bus);
	spin_unlock_irqrestore(&inject_lock, flags);
	return ops->read(bus, devfn, where, size, val);
}
