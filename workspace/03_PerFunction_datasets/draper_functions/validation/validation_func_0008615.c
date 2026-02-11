calc_attenuation_adip(int amount)
{
	int atten;
	atten = (amount + 12) / 24;
	atten = (atten * 8) / 3;
	if (atten > 255) atten = 255;
	if (atten < 0) atten = 0;
	return atten;
}
