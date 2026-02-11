cs4271_probe(struct device *dev, struct regmap *regmap)
{
	struct cs4271_private *cs4271;
	int ret;

	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	ret = cs4271_common_probe(dev, &cs4271);
	if (ret < 0)
		return ret;

	dev_set_drvdata(dev, cs4271);
	cs4271->regmap = regmap;

	return snd_soc_register_codec(dev, &soc_codec_dev_cs4271, &cs4271_dai,
				      1);
}
