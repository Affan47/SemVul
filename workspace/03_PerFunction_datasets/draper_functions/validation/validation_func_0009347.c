twl4030_sih_setup(struct device *dev, int module, int irq_base)
{
	int			sih_mod;
	const struct sih	*sih = NULL;
	struct sih_agent	*agent;
	int			i, irq;
	int			status = -EINVAL;


	for (sih_mod = 0, sih = sih_modules; sih_mod < nr_sih_modules;
			sih_mod++, sih++) {
		if (sih->module == module && sih->set_cor) {
			status = 0;
			break;
		}
	}

	if (status < 0)
		return status;

	agent = kzalloc(sizeof(*agent), GFP_KERNEL);
	if (!agent)
		return -ENOMEM;

	agent->irq_base = irq_base;
	agent->sih = sih;
	agent->imr = ~0;
	mutex_init(&agent->irq_lock);

	for (i = 0; i < sih->bits; i++) {
		irq = irq_base + i;

		irq_set_chip_data(irq, agent);
		irq_set_chip_and_handler(irq, &twl4030_sih_irq_chip,
					 handle_edge_irq);
		irq_set_nested_thread(irq, 1);
		activate_irq(irq);
	}


	irq = sih_mod + twl4030_irq_base;
	irq_set_handler_data(irq, agent);
	agent->irq_name = kasprintf(GFP_KERNEL, "twl4030_%s", sih->name);
	status = request_threaded_irq(irq, NULL, handle_twl4030_sih,
				      IRQF_EARLY_RESUME | IRQF_ONESHOT,
				      agent->irq_name ?: sih->name, NULL);

	dev_info(dev, "%s (irq %d) chaining IRQs %d..%d\n", sih->name,
			irq, irq_base, irq_base + i - 1);

	return status < 0 ? status : irq_base;
}
