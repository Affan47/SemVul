smt_stop_watchdog(struct s_smc *smc)
{
	SK_UNUSED(smc) ;
#ifndef	DEBUG

#ifdef	PCI
	if (smc->hw.wdog_used) {
		outpw(ADDR(B2_WDOG_CRTL),TIM_STOP) ;
	}
#endif

#endif
}
