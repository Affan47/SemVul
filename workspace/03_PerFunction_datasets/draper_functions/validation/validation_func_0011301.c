snd_emu1010_output_source_get(struct snd_kcontrol *kcontrol,
                                 struct snd_ctl_elem_value *ucontrol)
{
	struct snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	unsigned int channel;

	channel = (kcontrol->private_value) & 0xff;

	if (channel >= 24 ||
	    (emu->card_capabilities->emu_model == EMU_MODEL_EMU1616 &&
	     channel >= 18))
		return -EINVAL;
	ucontrol->value.enumerated.item[0] = emu->emu1010.output_source[channel];
	return 0;
}
