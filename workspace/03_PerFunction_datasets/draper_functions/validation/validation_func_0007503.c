tegra_alc5632_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct snd_soc_card *card = &snd_soc_tegra_alc5632;
	struct tegra_alc5632 *alc5632;
	int ret;

	alc5632 = devm_kzalloc(&pdev->dev,
			sizeof(struct tegra_alc5632), GFP_KERNEL);
	if (!alc5632) {
		dev_err(&pdev->dev, "Can't allocate tegra_alc5632\n");
		return -ENOMEM;
	}

	card->dev = &pdev->dev;
	platform_set_drvdata(pdev, card);
	snd_soc_card_set_drvdata(card, alc5632);

	alc5632->gpio_hp_det = of_get_named_gpio(np, "nvidia,hp-det-gpios", 0);
	if (alc5632->gpio_hp_det == -EPROBE_DEFER)
		return -EPROBE_DEFER;

	ret = snd_soc_of_parse_card_name(card, "nvidia,model");
	if (ret)
		goto err;

	ret = snd_soc_of_parse_audio_routing(card, "nvidia,audio-routing");
	if (ret)
		goto err;

	tegra_alc5632_dai.codec_of_node = of_parse_phandle(
			pdev->dev.of_node, "nvidia,audio-codec", 0);

	if (!tegra_alc5632_dai.codec_of_node) {
		dev_err(&pdev->dev,
			"Property 'nvidia,audio-codec' missing or invalid\n");
		ret = -EINVAL;
		goto err;
	}

	tegra_alc5632_dai.cpu_of_node = of_parse_phandle(np,
			"nvidia,i2s-controller", 0);
	if (!tegra_alc5632_dai.cpu_of_node) {
		dev_err(&pdev->dev,
			"Property 'nvidia,i2s-controller' missing or invalid\n");
		ret = -EINVAL;
		goto err;
	}

	tegra_alc5632_dai.platform_of_node = tegra_alc5632_dai.cpu_of_node;

	ret = tegra_asoc_utils_init(&alc5632->util_data, &pdev->dev);
	if (ret)
		goto err;

	ret = snd_soc_register_card(card);
	if (ret) {
		dev_err(&pdev->dev, "snd_soc_register_card failed (%d)\n",
			ret);
		goto err_fini_utils;
	}

	return 0;

err_fini_utils:
	tegra_asoc_utils_fini(&alc5632->util_data);
err:
	return ret;
}
