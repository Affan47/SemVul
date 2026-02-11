stmmac_mdio_register(struct net_device *ndev)
{
	int err = 0;
	struct mii_bus *new_bus;
	int *irqlist;
	struct stmmac_priv *priv = netdev_priv(ndev);
	struct stmmac_mdio_bus_data *mdio_bus_data = priv->plat->mdio_bus_data;
	int addr, found;

	if (!mdio_bus_data)
		return 0;

	new_bus = mdiobus_alloc();
	if (new_bus == NULL)
		return -ENOMEM;

	if (mdio_bus_data->irqs) {
		irqlist = mdio_bus_data->irqs;
	} else {
		for (addr = 0; addr < PHY_MAX_ADDR; addr++)
			priv->mii_irq[addr] = PHY_POLL;
		irqlist = priv->mii_irq;
	}

#ifdef CONFIG_OF
	if (priv->device->of_node)
		mdio_bus_data->reset_gpio = -1;
#endif

	new_bus->name = "stmmac";
	new_bus->read = &stmmac_mdio_read;
	new_bus->write = &stmmac_mdio_write;
	new_bus->reset = &stmmac_mdio_reset;
	snprintf(new_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		 new_bus->name, priv->plat->bus_id);
	new_bus->priv = ndev;
	new_bus->irq = irqlist;
	new_bus->phy_mask = mdio_bus_data->phy_mask;
	new_bus->parent = priv->device;
	err = mdiobus_register(new_bus);
	if (err != 0) {
		pr_err("%s: Cannot register as MDIO bus\n", new_bus->name);
		goto bus_register_fail;
	}

	found = 0;
	for (addr = 0; addr < PHY_MAX_ADDR; addr++) {
		struct phy_device *phydev = new_bus->phy_map[addr];
		if (phydev) {
			int act = 0;
			char irq_num[4];
			char *irq_str;


			if ((mdio_bus_data->irqs == NULL) &&
			    (mdio_bus_data->probed_phy_irq > 0)) {
				irqlist[addr] = mdio_bus_data->probed_phy_irq;
				phydev->irq = mdio_bus_data->probed_phy_irq;
			}


			if (priv->plat->phy_addr == -1)
				priv->plat->phy_addr = addr;

			act = (priv->plat->phy_addr == addr);
			switch (phydev->irq) {
			case PHY_POLL:
				irq_str = "POLL";
				break;
			case PHY_IGNORE_INTERRUPT:
				irq_str = "IGNORE";
				break;
			default:
				sprintf(irq_num, "%d", phydev->irq);
				irq_str = irq_num;
				break;
			}
			pr_info("%s: PHY ID %08x at %d IRQ %s (%s)%s\n",
				ndev->name, phydev->phy_id, addr,
				irq_str, dev_name(&phydev->dev),
				act ? " active" : "");
			found = 1;
		}
	}

	if (!found) {
		pr_warn("%s: No PHY found\n", ndev->name);
		mdiobus_unregister(new_bus);
		mdiobus_free(new_bus);
		return -ENODEV;
	}

	priv->mii = new_bus;

	return 0;

bus_register_fail:
	mdiobus_free(new_bus);
	return err;
}
