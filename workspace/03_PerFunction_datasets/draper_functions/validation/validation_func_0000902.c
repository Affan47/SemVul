rme9652_spdif_set_bit (struct snd_rme9652 *rme9652, int mask, int onoff)
{
	if (onoff)
		rme9652->control_register |= mask;
	else
		rme9652->control_register &= ~mask;

	rme9652_write(rme9652, RME9652_control_register, rme9652->control_register);
}
