snd_trident_free_synth_channel(struct snd_trident *trident, int channel)
{
	if (channel < 0 || channel > 31)
		return;
	channel &= 0x1f;
	if (trident->ChanMap[T4D_BANK_A] & (1 << channel)) {
		trident->ChanMap[T4D_BANK_A] &= ~(1 << channel);
		trident->synth.ChanSynthCount--;
	}
}
