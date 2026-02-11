vx855gpio_set(struct gpio_chip *gpio, unsigned int nr,
			  int val)
{
	struct vx855_gpio *vg = container_of(gpio, struct vx855_gpio, gpio);
	unsigned long flags;
	u_int32_t reg_out;


	if (nr < NR_VX855_GPI)
		return;

	spin_lock_irqsave(&vg->lock, flags);
	reg_out = inl(vg->io_gpo);
	if (nr < NR_VX855_GPInO) {
		if (val)
			reg_out |= gpo_o_bit(nr - NR_VX855_GPI);
		else
			reg_out &= ~gpo_o_bit(nr - NR_VX855_GPI);
	} else {
		if (val)
			reg_out |= gpio_o_bit(nr - NR_VX855_GPInO);
		else
			reg_out &= ~gpio_o_bit(nr - NR_VX855_GPInO);
	}
	outl(reg_out, vg->io_gpo);
	spin_unlock_irqrestore(&vg->lock, flags);
}
