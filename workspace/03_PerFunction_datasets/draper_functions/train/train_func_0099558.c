maya_gpio_sw_get(struct snd_kcontrol *kcontrol,
			    struct snd_ctl_elem_value *ucontrol)
{
	struct snd_maya44 *chip = snd_kcontrol_chip(kcontrol);
	unsigned int shift = GET_GPIO_VAL_SHIFT(kcontrol->private_value);
	unsigned int val;

	val = (snd_ice1712_gpio_read(chip->ice) >> shift) & 1;
	if (GET_GPIO_VAL_INV(kcontrol->private_value))
		val = !val;
	ucontrol->value.integer.value[0] = val;
	return 0;
}
