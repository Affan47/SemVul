lt3593_led_work(struct work_struct *work)
{
	int pulses;
	struct lt3593_led_data *led_dat =
		container_of(work, struct lt3593_led_data, work);


	if (led_dat->new_level == 0) {
		gpio_set_value_cansleep(led_dat->gpio, 0);
		return;
	}

	pulses = 32 - (led_dat->new_level * 32) / 255;

	if (pulses == 0) {
		gpio_set_value_cansleep(led_dat->gpio, 0);
		mdelay(1);
		gpio_set_value_cansleep(led_dat->gpio, 1);
		return;
	}

	gpio_set_value_cansleep(led_dat->gpio, 1);

	while (pulses--) {
		gpio_set_value_cansleep(led_dat->gpio, 0);
		udelay(1);
		gpio_set_value_cansleep(led_dat->gpio, 1);
		udelay(1);
	}
}
