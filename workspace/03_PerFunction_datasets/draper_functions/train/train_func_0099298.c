rcSibUpdate_ht(struct ath_softc_tgt *sc, struct ath_node_target *an,
	       A_UINT32 capflag, A_BOOL keepState, struct ieee80211_rate  *pRateSet)
{
	RATE_TABLE_11N *pRateTable = 0;
	struct atheros_node *pSib = ATH_NODE_ATHEROS(an);
	struct atheros_softc *asc = (struct atheros_softc*)sc->sc_rc;
	A_UINT8 *phtMcs = (A_UINT8*)&pRateSet->htrates;
	TX_RATE_CTRL *pRc = (TX_RATE_CTRL *)(pSib);
	PHY_STATE_CTRL mPhyCtrlState;

	A_UINT8 i, j, k, hi = 0, htHi = 0;

	pRateTable = (RATE_TABLE_11N*)asc->hwRateTable[sc->sc_curmode];


	pRc->rateTableSize = MAX_TX_RATE_TBL;


	for (i = 0 ; (i < pRc->rateTableSize) && (!keepState); i++) {
		pRc->state[i].per       = 0;
	}


	rcInitValidTxMask(pRc);

	for (i = 0; i < WLAN_RC_PHY_MAX; i++) {
		for (j = 0; j < MAX_TX_RATE_TBL; j++) {
			mPhyCtrlState.validPhyRateIndex[i][j] = 0;
		}
		mPhyCtrlState.validPhyRateCount[i] = 0;
	}

	pRc->rcPhyMode = (capflag & WLAN_RC_40_FLAG);

	if (pRateSet == NULL || !pRateSet->rates.rs_nrates) {

		hi = rcSibInitValidRates(pRateTable, pRc, capflag, &mPhyCtrlState);
	} else {

		hi = rcSibSetValidRates(pRateTable, pRc, &(pRateSet->rates),
					capflag, an, &mPhyCtrlState);

		if (capflag & WLAN_RC_HT_FLAG) {
			htHi = rcSibSetValidHtRates(pRateTable, pRc, phtMcs,
						    capflag, an, &mPhyCtrlState);
		}

		hi = A_MAX(hi, htHi);
	}

	pRc->rateTableSize = hi + 1;
	pRc->rateMaxPhy    = 0;

	ASSERT(pRc->rateTableSize <= MAX_TX_RATE_TBL);

	for (i = 0, k = 0; i < WLAN_RC_PHY_MAX; i++) {
		for (j = 0; j < mPhyCtrlState.validPhyRateCount[i]; j++) {
			pRc->validRateIndex[k++] = mPhyCtrlState.validPhyRateIndex[i][j];
		}

		if (!rcIsValidPhyRate(i, pRateTable->initialRateMax, TRUE) ||
		    !mPhyCtrlState.validPhyRateCount[i])
			continue;

		pRc->rateMaxPhy = mPhyCtrlState.validPhyRateIndex[i][j-1];
	}

	ASSERT(pRc->rateTableSize <= MAX_TX_RATE_TBL);
	ASSERT(k <= MAX_TX_RATE_TBL);

	pRc->rateMaxPhy = pRc->validRateIndex[k-4];
	pRc->maxValidRate = k;

	rcSortValidRates(pRateTable, pRc);
}
