highbank_set_em_messages(struct device *dev,
					struct ahci_host_priv *hpriv,
					struct ata_port_info *pi)
{
	struct device_node *np = dev->of_node;
	struct ecx_plat_data *pdata = hpriv->plat_data;
	int i;
	int err;

	for (i = 0; i < SGPIO_PINS; i++) {
		err = of_get_named_gpio(np, "calxeda,sgpio-gpio", i);
		if (IS_ERR_VALUE(err))
			return;

		pdata->sgpio_gpio[i] = err;
		err = gpio_request(pdata->sgpio_gpio[i], "CX SGPIO");
		if (err) {
			pr_err("sata_highbank gpio_request %d failed: %d\n",
					i, err);
			return;
		}
		gpio_direction_output(pdata->sgpio_gpio[i], 1);
	}
	of_property_read_u32_array(np, "calxeda,led-order",
						pdata->port_to_sgpio,
						pdata->n_ports);
	if (of_property_read_u32(np, "calxeda,pre-clocks", &pdata->pre_clocks))
		pdata->pre_clocks = 0;
	if (of_property_read_u32(np, "calxeda,post-clocks",
				&pdata->post_clocks))
		pdata->post_clocks = 0;


	hpriv->em_loc = 0;
	hpriv->em_buf_sz = 4;
	hpriv->em_msg_type = EM_MSG_TYPE_LED;
	pi->flags |= ATA_FLAG_EM | ATA_FLAG_SW_ACTIVITY;
}
