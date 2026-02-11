SMP_NewBan(const uint8_t *ban, unsigned ln)
{
	struct smp_sc *sc;

	VTAILQ_FOREACH(sc, &silos, list) {
		smp_appendban(sc, &sc->ban1, ln, ban);
		smp_appendban(sc, &sc->ban2, ln, ban);
	}
}
