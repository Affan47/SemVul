p54_register_common(struct ieee80211_hw *dev, struct device *pdev)
{
	struct p54_common __maybe_unused *priv = dev->priv;
	int err;

	err = ieee80211_register_hw(dev);
	if (err) {
		dev_err(pdev, "Cannot register device (%d).\n", err);
		return err;
	}
	priv->registered = true;

#ifdef CONFIG_P54_LEDS
	err = p54_init_leds(priv);
	if (err) {
		p54_unregister_common(dev);
		return err;
	}
#endif

	dev_info(pdev, "is registered as '%s'\n", wiphy_name(dev->wiphy));
	return 0;
}
