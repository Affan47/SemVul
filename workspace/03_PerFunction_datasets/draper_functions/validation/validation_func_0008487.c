ath9k_reg_rmw(void *hw_priv, u32 reg_offset, u32 set, u32 clr)
{
	struct ath_hw *ah = (struct ath_hw *) hw_priv;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath_softc *sc = (struct ath_softc *) common->priv;
	unsigned long uninitialized_var(flags);
	u32 val;

	if (NR_CPUS > 1 && ah->config.serialize_regmode == SER_REG_MODE_ON) {
		spin_lock_irqsave(&sc->sc_serial_rw, flags);
		val = __ath9k_reg_rmw(sc, reg_offset, set, clr);
		spin_unlock_irqrestore(&sc->sc_serial_rw, flags);
	} else
		val = __ath9k_reg_rmw(sc, reg_offset, set, clr);

	return val;
}
