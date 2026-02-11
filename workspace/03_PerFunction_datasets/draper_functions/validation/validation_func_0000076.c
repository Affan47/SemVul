sci_port_is_wide(struct isci_port *iport)
{
	u32 index;
	u32 phy_count = 0;

	for (index = 0; index < SCI_MAX_PHYS; index++) {
		if (iport->phy_table[index] != NULL) {
			phy_count++;
		}
	}

	return phy_count != 1;
}
