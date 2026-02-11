snd_mts64_remove(struct platform_device *pdev)
{
	struct snd_card *card = platform_get_drvdata(pdev);

	if (card)
		snd_card_free(card);

	return 0;
}
