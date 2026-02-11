ath_tgt_txq_setup(struct ath_softc_tgt *sc)
{
	a_int32_t qnum;
	struct ath_txq *txq;

	sc->sc_txqsetup=0;

	for (qnum=0;qnum<HAL_NUM_TX_QUEUES;qnum++) {
		txq= &sc->sc_txq[qnum];
		txq->axq_qnum = qnum;
		txq->axq_link = NULL;
		asf_tailq_init(&txq->axq_q);
		txq->axq_depth = 0;
		txq->axq_linkbuf = NULL;
		asf_tailq_init(&txq->axq_tidq);
		sc->sc_txqsetup |= 1<<qnum;
	}

	sc->sc_uapsdq  = &sc->sc_txq[UAPSDQ_NUM];
	sc->sc_cabq    = &sc->sc_txq[CABQ_NUM];

	sc->sc_ac2q[WME_AC_BE]  = &sc->sc_txq[0];
	sc->sc_ac2q[WME_AC_BK]  = &sc->sc_txq[1];
	sc->sc_ac2q[WME_AC_VI]  = &sc->sc_txq[2];
	sc->sc_ac2q[WME_AC_VO]  = &sc->sc_txq[3];

	return;
#undef N
}
