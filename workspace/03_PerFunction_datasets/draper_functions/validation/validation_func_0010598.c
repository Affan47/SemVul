of_mdiobus_register(struct mii_bus *mdio, struct device_node *np)
{
	struct device_node *child;
	const __be32 *paddr;
	bool scanphys = false;
	int addr, rc, i;


	mdio->phy_mask = ~0;


	if (mdio->irq)
		for (i=0; i<PHY_MAX_ADDR; i++)
			mdio->irq[i] = PHY_POLL;

	mdio->dev.of_node = np;


	rc = mdiobus_register(mdio);
	if (rc)
		return rc;


	for_each_available_child_of_node(np, child) {
		addr = of_mdio_parse_addr(&mdio->dev, child);
		if (addr < 0) {
			scanphys = true;
			continue;
		}

		rc = of_mdiobus_register_phy(mdio, child, addr);
		if (rc)
			continue;
	}

	if (!scanphys)
		return 0;


	for_each_available_child_of_node(np, child) {

		paddr = of_get_property(child, "reg", NULL);
		if (paddr)
			continue;

		for (addr = 0; addr < PHY_MAX_ADDR; addr++) {

			if (mdio->phy_map[addr])
				continue;


			dev_info(&mdio->dev, "scan phy %s at address %i\n",
				 child->name, addr);

			rc = of_mdiobus_register_phy(mdio, child, addr);
			if (rc)
				continue;
		}
	}

	return 0;
}
