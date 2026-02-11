ap_cs8427_codec_deassert(struct snd_ice1712 *ice, unsigned char tmp)
{
	switch (ice->eeprom.subvendor) {
	case ICE1712_SUBDEVICE_DELTA1010E:
	case ICE1712_SUBDEVICE_DELTA1010LT:
		tmp &= ~ICE1712_DELTA_1010LT_CS;
		tmp |= ICE1712_DELTA_1010LT_CS_NONE;
		break;
	case ICE1712_SUBDEVICE_AUDIOPHILE:
	case ICE1712_SUBDEVICE_DELTA410:
		tmp |= ICE1712_DELTA_AP_CS_DIGITAL;
		break;
	case ICE1712_SUBDEVICE_DELTA66E:
		tmp |= ICE1712_DELTA_66E_CS_CS8427;
		break;
	case ICE1712_SUBDEVICE_VX442:
		tmp |= ICE1712_VX442_CS_DIGITAL;
		break;
	}
	snd_ice1712_write(ice, ICE1712_IREG_GPIO_DATA, tmp);
}
