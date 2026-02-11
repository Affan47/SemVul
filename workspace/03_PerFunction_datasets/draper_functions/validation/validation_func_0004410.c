gpiochip_find(void *data,
				int (*match)(struct gpio_chip *chip,
					     void *data))
{
	struct gpio_chip *chip;
	unsigned long flags;

	spin_lock_irqsave(&gpio_lock, flags);
	list_for_each_entry(chip, &gpio_chips, list)
		if (match(chip, data))
			break;


	if (&chip->list == &gpio_chips)
		chip = NULL;
	spin_unlock_irqrestore(&gpio_lock, flags);

	return chip;
}
