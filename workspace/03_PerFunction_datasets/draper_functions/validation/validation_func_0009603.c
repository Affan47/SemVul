snd_soundfont_close_check(struct snd_sf_list *sflist, int client)
{
	unsigned long flags;
	spin_lock_irqsave(&sflist->lock, flags);
	if (sflist->open_client == client)  {
		spin_unlock_irqrestore(&sflist->lock, flags);
		return close_patch(sflist);
	}
	spin_unlock_irqrestore(&sflist->lock, flags);
	return 0;
}
