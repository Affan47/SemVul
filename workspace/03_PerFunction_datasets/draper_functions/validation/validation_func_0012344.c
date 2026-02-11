radio_stop(void)
{
	radio_mute();

	if (dev)
		dev->finalize (dev);
	if (alsa_loopback)
		fprintf(stderr, "alsa: Stream stopped\n");
}
