p54_reset_stats(struct p54_common *priv)
{
	struct ieee80211_channel *chan = priv->curchan;

	if (chan) {
		struct survey_info *info = &priv->survey[chan->hw_value];


		info->time = 0;
		info->time_busy = 0;
		info->time_tx = 0;
	}

	priv->update_stats = true;
	priv->survey_raw.active = 0;
	priv->survey_raw.cca = 0;
	priv->survey_raw.tx = 0;
}
