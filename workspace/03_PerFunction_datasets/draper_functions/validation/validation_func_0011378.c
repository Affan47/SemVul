sdv_register_irqsupport(struct sdv_gpio_chip_data *sd,
		struct pci_dev *pdev)
{
	struct irq_chip_type *ct;
	int ret;

	sd->irq_base = irq_alloc_descs(-1, 0, SDV_NUM_PUB_GPIOS, -1);
	if (sd->irq_base < 0)
		return sd->irq_base;


	writel(0, sd->gpio_pub_base + GPIO_INT);
	writel((1 << 11) - 1, sd->gpio_pub_base + GPSTR);

	ret = request_irq(pdev->irq, sdv_gpio_pub_irq_handler, IRQF_SHARED,
			"sdv_gpio", sd);
	if (ret)
		goto out_free_desc;


	sd->gc = irq_alloc_generic_chip("sdv-gpio", 1, sd->irq_base,
			sd->gpio_pub_base, handle_fasteoi_irq);
	if (!sd->gc) {
		ret = -ENOMEM;
		goto out_free_irq;
	}

	sd->gc->private = sd;
	ct = sd->gc->chip_types;
	ct->type = IRQ_TYPE_LEVEL_HIGH | IRQ_TYPE_LEVEL_LOW;
	ct->regs.eoi = GPSTR;
	ct->regs.mask = GPIO_INT;
	ct->chip.irq_mask = irq_gc_mask_clr_bit;
	ct->chip.irq_unmask = irq_gc_mask_set_bit;
	ct->chip.irq_eoi = irq_gc_eoi;
	ct->chip.irq_set_type = sdv_gpio_pub_set_type;

	irq_setup_generic_chip(sd->gc, IRQ_MSK(SDV_NUM_PUB_GPIOS),
			IRQ_GC_INIT_MASK_CACHE, IRQ_NOREQUEST,
			IRQ_LEVEL | IRQ_NOPROBE);

	sd->id = irq_domain_add_legacy(pdev->dev.of_node, SDV_NUM_PUB_GPIOS,
				sd->irq_base, 0, &irq_domain_sdv_ops, sd);
	if (!sd->id) {
		ret = -ENODEV;
		goto out_free_irq;
	}
	return 0;
out_free_irq:
	free_irq(pdev->irq, sd);
out_free_desc:
	irq_free_descs(sd->irq_base, SDV_NUM_PUB_GPIOS);
	return ret;
}
