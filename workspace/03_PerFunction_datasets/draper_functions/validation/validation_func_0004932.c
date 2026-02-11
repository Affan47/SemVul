ar5008_hw_do_getnf(struct ath_hw *ah,
			      int16_t nfarray[NUM_NF_READINGS])
{
	int16_t nf;

	nf = MS(REG_READ(ah, AR_PHY_CCA), AR_PHY_MINCCA_PWR);
	nfarray[0] = sign_extend32(nf, 8);

	nf = MS(REG_READ(ah, AR_PHY_CH1_CCA), AR_PHY_CH1_MINCCA_PWR);
	nfarray[1] = sign_extend32(nf, 8);

	nf = MS(REG_READ(ah, AR_PHY_CH2_CCA), AR_PHY_CH2_MINCCA_PWR);
	nfarray[2] = sign_extend32(nf, 8);

	if (!IS_CHAN_HT40(ah->curchan))
		return;

	nf = MS(REG_READ(ah, AR_PHY_EXT_CCA), AR_PHY_EXT_MINCCA_PWR);
	nfarray[3] = sign_extend32(nf, 8);

	nf = MS(REG_READ(ah, AR_PHY_CH1_EXT_CCA), AR_PHY_CH1_EXT_MINCCA_PWR);
	nfarray[4] = sign_extend32(nf, 8);

	nf = MS(REG_READ(ah, AR_PHY_CH2_EXT_CCA), AR_PHY_CH2_EXT_MINCCA_PWR);
	nfarray[5] = sign_extend32(nf, 8);
}
