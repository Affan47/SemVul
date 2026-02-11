snd_saa7134_capsrc_get(struct snd_kcontrol * kcontrol,
				  struct snd_ctl_elem_value * ucontrol)
{
	snd_card_saa7134_t *chip = snd_kcontrol_chip(kcontrol);
	int addr = kcontrol->private_value;

	spin_lock_irq(&chip->mixer_lock);
	if (chip->capture_source_addr == addr) {
		ucontrol->value.integer.value[0] = chip->capture_source[0];
		ucontrol->value.integer.value[1] = chip->capture_source[1];
	} else {
		ucontrol->value.integer.value[0] = 0;
		ucontrol->value.integer.value[1] = 0;
	}
	spin_unlock_irq(&chip->mixer_lock);

	return 0;
}
