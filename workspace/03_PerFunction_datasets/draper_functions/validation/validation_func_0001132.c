ath9k_mci_set_txpower(struct ath_softc *sc, bool setchannel,
			   bool concur_tx)
{
	struct ath_hw *ah = sc->sc_ah;
	struct ath9k_hw_mci *mci_hw = &sc->sc_ah->btcoex_hw.mci;
	bool old_concur_tx = mci_hw->concur_tx;

	if (!(mci_hw->config & ATH_MCI_CONFIG_CONCUR_TX)) {
		mci_hw->concur_tx = false;
		return;
	}

	if (!IS_CHAN_2GHZ(ah->curchan))
		return;

	if (setchannel) {
		struct ath9k_hw_cal_data *caldata = &sc->cur_chan->caldata;
		if (IS_CHAN_HT40PLUS(ah->curchan) &&
		    (ah->curchan->channel > caldata->channel) &&
		    (ah->curchan->channel <= caldata->channel + 20))
			return;
		if (IS_CHAN_HT40MINUS(ah->curchan) &&
		    (ah->curchan->channel < caldata->channel) &&
		    (ah->curchan->channel >= caldata->channel - 20))
			return;
		mci_hw->concur_tx = false;
	} else
		mci_hw->concur_tx = concur_tx;

	if (old_concur_tx != mci_hw->concur_tx)
		ath9k_hw_set_txpowerlimit(ah, sc->cur_chan->txpower, false);
}
