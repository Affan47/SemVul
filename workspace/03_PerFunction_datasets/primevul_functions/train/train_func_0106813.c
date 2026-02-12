static void sunkbd_reinit(struct work_struct *work)
{
	struct sunkbd *sunkbd = container_of(work, struct sunkbd, tq);


	wait_event_interruptible_timeout(sunkbd->wait,
					 sunkbd->reset >= 0 || !sunkbd->enabled,
					 HZ);

	if (sunkbd->reset >= 0 && sunkbd->enabled)
		sunkbd_set_leds_beeps(sunkbd);
}
