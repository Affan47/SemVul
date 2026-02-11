ath9k_hw_loadnf(struct ath_hw *ah, struct ath9k_channel *chan)
{
	struct ath9k_nfcal_hist *h = NULL;
	unsigned i, j;
	int32_t val;
	u8 chainmask = (ah->rxchainmask << 3) | ah->rxchainmask;
	s16 default_nf = ath9k_hw_get_default_nf(ah, chan);

	if (ah->caldata)
		h = ah->caldata->nfCalHist;

	for (i = 0; i < NUM_NF_READINGS; i++) {
		if (chainmask & (1 << i)) {
			s16 nfval;

			if (i >= AR5416_MAX_CHAINS)
				continue;

			if (h)
				nfval = h[i].privNF;
			else
				nfval = default_nf;

			val = REG_READ(ah, ah->nf_regs[i]);
			val &= 0xFFFFFE00;
			val |= (((u32) nfval << 1) & 0x1ff);
			REG_WRITE(ah, ah->nf_regs[i], val);
		}
	}


	REG_CLR_BIT(ah, AR_PHY_AGC_CONTROL,
		    AR_PHY_AGC_CONTROL_ENABLE_NF);
	REG_CLR_BIT(ah, AR_PHY_AGC_CONTROL,
		    AR_PHY_AGC_CONTROL_NO_UPDATE_NF);
	REG_SET_BIT(ah, AR_PHY_AGC_CONTROL, AR_PHY_AGC_CONTROL_NF);


	for (j = 0; j < 10000; j++) {
		if ((REG_READ(ah, AR_PHY_AGC_CONTROL) &
		     AR_PHY_AGC_CONTROL_NF) == 0)
			break;
		udelay(10);
	}


	if (j == 10000) {
		DBG("ath9k: "
			"Timeout while waiting for nf to load: AR_PHY_AGC_CONTROL=0x%x\n",
			REG_READ(ah, AR_PHY_AGC_CONTROL));
		return;
	}


	ENABLE_REGWRITE_BUFFER(ah);
	for (i = 0; i < NUM_NF_READINGS; i++) {
		if (chainmask & (1 << i)) {
			if (i >= AR5416_MAX_CHAINS)
				continue;

			val = REG_READ(ah, ah->nf_regs[i]);
			val &= 0xFFFFFE00;
			val |= (((u32) (-50) << 1) & 0x1ff);
			REG_WRITE(ah, ah->nf_regs[i], val);
		}
	}
	REGWRITE_BUFFER_FLUSH(ah);
}
