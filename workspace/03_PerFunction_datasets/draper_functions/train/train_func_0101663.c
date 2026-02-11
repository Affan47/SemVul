amd_gpio_set(struct gpio_chip *chip, unsigned offset, int value)
{
	struct amd_gpio *agp = to_agp(chip);
	u8 temp;
	unsigned long flags;

	spin_lock_irqsave(&agp->lock, flags);
	temp = ioread8(agp->pm + AMD_REG_GPIO(offset));
	temp = (temp & AMD_GPIO_DEBOUNCE) | AMD_GPIO_MODE_OUT | (value ? AMD_GPIO_X_OUT_HI : AMD_GPIO_X_OUT_LOW);
	iowrite8(temp, agp->pm + AMD_REG_GPIO(offset));
	spin_unlock_irqrestore(&agp->lock, flags);

	dev_dbg(&agp->pdev->dev, "Setting gpio %d, value %d, reg=%02x\n", offset, !!value, temp);
}
