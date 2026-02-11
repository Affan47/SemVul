atc_resume(struct ct_atc *atc)
{
	int err = 0;


	err = atc_hw_resume(atc);
	if (err < 0) {
		dev_err(atc->card->dev,
			"pci_enable_device failed, disabling device\n");
		snd_card_disconnect(atc->card);
		return err;
	}

	err = atc_resources_resume(atc);
	if (err < 0)
		return err;

	snd_power_change_state(atc->card, SNDRV_CTL_POWER_D0);

	return 0;
}
