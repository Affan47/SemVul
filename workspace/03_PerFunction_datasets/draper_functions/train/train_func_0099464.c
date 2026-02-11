wake_up_cmv_ack(struct uea_softc *sc)
{
	BUG_ON(sc->cmv_ack);
	sc->cmv_ack = 1;
	wake_up(&sc->sync_q);
}
