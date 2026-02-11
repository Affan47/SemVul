idio_16_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	struct idio_16_gpio *const idio16gpio = to_idio16gpio(chip);
	const unsigned BIT_MASK = 1U << (offset-16);

	if (offset < 16)
		return -EINVAL;

	if (offset < 24)
		return !!(inb(idio16gpio->base + 1) & BIT_MASK);

	return !!(inb(idio16gpio->base + 5) & (BIT_MASK>>8));
}
