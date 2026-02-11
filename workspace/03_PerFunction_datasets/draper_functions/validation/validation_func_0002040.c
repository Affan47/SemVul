gpiochip_free_hogs(struct gpio_chip *chip)
{
	int id;

	for (id = 0; id < chip->ngpio; id++) {
		if (test_bit(FLAG_IS_HOGGED, &chip->desc[id].flags))
			gpiochip_free_own_desc(&chip->desc[id]);
	}
}
