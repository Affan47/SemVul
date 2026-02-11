ath_chanctx_init(struct ath_softc *sc)
{
	struct ath_chanctx *ctx;
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	struct ieee80211_supported_band *sband;
	struct ieee80211_channel *chan;
	int i, j;

	sband = &common->sbands[IEEE80211_BAND_2GHZ];
	if (!sband->n_channels)
		sband = &common->sbands[IEEE80211_BAND_5GHZ];

	chan = &sband->channels[0];
	for (i = 0; i < ATH9K_NUM_CHANCTX; i++) {
		ctx = &sc->chanctx[i];
		cfg80211_chandef_create(&ctx->chandef, chan, NL80211_CHAN_HT20);
		INIT_LIST_HEAD(&ctx->vifs);
		ctx->txpower = ATH_TXPOWER_MAX;
		ctx->flush_timeout = HZ / 5;
		for (j = 0; j < ARRAY_SIZE(ctx->acq); j++)
			INIT_LIST_HEAD(&ctx->acq[j]);
	}
}
