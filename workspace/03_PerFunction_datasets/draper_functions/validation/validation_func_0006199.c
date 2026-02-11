snd_emu10k1_spdif_get(struct snd_kcontrol *kcontrol,
                                 struct snd_ctl_elem_value *ucontrol)
{
	struct snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	unsigned int idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	unsigned long flags;


	if (idx >= 3)
		return -EINVAL;
	spin_lock_irqsave(&emu->reg_lock, flags);
	ucontrol->value.iec958.status[0] = (emu->spdif_bits[idx] >> 0) & 0xff;
	ucontrol->value.iec958.status[1] = (emu->spdif_bits[idx] >> 8) & 0xff;
	ucontrol->value.iec958.status[2] = (emu->spdif_bits[idx] >> 16) & 0xff;
	ucontrol->value.iec958.status[3] = (emu->spdif_bits[idx] >> 24) & 0xff;
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	return 0;
}
