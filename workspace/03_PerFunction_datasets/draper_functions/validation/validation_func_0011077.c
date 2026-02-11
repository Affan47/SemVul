snd_ymfpci_drec_source_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *value)
{
	struct snd_ymfpci *chip = snd_kcontrol_chip(kcontrol);
	u16 reg;

	spin_lock_irq(&chip->reg_lock);
	reg = snd_ymfpci_readw(chip, YDSXGR_GLOBALCTRL);
	spin_unlock_irq(&chip->reg_lock);
	if (!(reg & 0x100))
		value->value.enumerated.item[0] = 0;
	else
		value->value.enumerated.item[0] = 1 + ((reg & 0x200) != 0);
	return 0;
}
