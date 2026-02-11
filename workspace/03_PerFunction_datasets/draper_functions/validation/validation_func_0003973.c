ath9k_hw_set_txpowerlimit(struct ath_hw *ah, u32 limit, bool test)
{
	struct ath_regulatory *reg = ath9k_hw_regulatory(ah);
	struct ath9k_channel *chan = ah->curchan;
	struct ieee80211_channel *channel = chan->chan;

	reg->power_limit = min_t(u32, limit, MAX_RATE_POWER);
	if (test)
		channel->max_power = MAX_RATE_POWER / 2;

	ath9k_hw_apply_txpower(ah, chan, test);

	if (test)
		channel->max_power = DIV_ROUND_UP(reg->max_power_level, 2);
}
