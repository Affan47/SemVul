snd_pcm_rate_bit_to_rate(unsigned int rate_bit)
{
	unsigned int i;

	for (i = 0; i < snd_pcm_known_rates.count; i++)
		if ((1u << i) == rate_bit)
			return snd_pcm_known_rates.list[i];
	return 0;
}
