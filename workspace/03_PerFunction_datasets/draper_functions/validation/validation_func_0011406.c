snd_ice1712_pro_ac97_write(struct snd_ac97 *ac97,
				       unsigned short reg,
				       unsigned short val)
{
	struct snd_ice1712 *ice = ac97->private_data;
	int tm;
	unsigned char old_cmd = 0;

	for (tm = 0; tm < 0x10000; tm++) {
		old_cmd = inb(ICEMT(ice, AC97_CMD));
		if (old_cmd & (ICE1712_AC97_WRITE | ICE1712_AC97_READ))
			continue;
		if (!(old_cmd & ICE1712_AC97_READY))
			continue;
		break;
	}
	outb(reg, ICEMT(ice, AC97_INDEX));
	outw(val, ICEMT(ice, AC97_DATA));
	old_cmd &= ~(ICE1712_AC97_PBK_VSR | ICE1712_AC97_CAP_VSR);
	outb(old_cmd | ICE1712_AC97_WRITE, ICEMT(ice, AC97_CMD));
	for (tm = 0; tm < 0x10000; tm++)
		if ((inb(ICEMT(ice, AC97_CMD)) & ICE1712_AC97_WRITE) == 0)
			break;
}
