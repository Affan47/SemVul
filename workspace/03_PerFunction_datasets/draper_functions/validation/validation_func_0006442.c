clear_arcofi(struct IsdnCardState *cs) {
	if (test_and_clear_bit(FLG_ARCOFI_TIMER, &cs->HW_Flags)) {
		del_timer(&cs->dc.isac.arcofitimer);
	}
}
