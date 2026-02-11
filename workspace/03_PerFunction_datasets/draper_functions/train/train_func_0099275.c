snd_ac97_free(struct snd_ac97 *ac97)
{
	if (ac97) {
#ifdef CONFIG_SND_AC97_POWER_SAVE
		cancel_delayed_work_sync(&ac97->power_work);
#endif
		snd_ac97_proc_done(ac97);
		if (ac97->bus)
			ac97->bus->codec[ac97->num] = NULL;
		if (ac97->private_free)
			ac97->private_free(ac97);
		kfree(ac97);
	}
	return 0;
}
