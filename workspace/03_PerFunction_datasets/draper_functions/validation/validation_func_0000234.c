sedlbauer_release(struct pcmcia_device *link)
{
	local_info_t *local = link->priv;
	dev_dbg(&link->dev, "sedlbauer_release(0x%p)\n", link);

	if (local) {
		if (local->cardnr >= 0) {

			HiSax_closecard(local->cardnr);
		}
	}

	pcmcia_disable_device(link);
}
