clk_register_gpio_gate(struct device *dev, const char *name,
		const char *parent_name, unsigned gpio, bool active_low,
		unsigned long flags)
{
	return clk_register_gpio(dev, name,
			(parent_name ? &parent_name : NULL),
			(parent_name ? 1 : 0), gpio, active_low, flags,
			&clk_gpio_gate_ops);
}
