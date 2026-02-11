update_68k_cycles (void)
{
	cycles_mult = 0;
	if (currprefs.m68k_speed >= 0 && !currprefs.cpu_cycle_exact) {
		if (currprefs.m68k_speed_throttle < 0) {
			cycles_mult = (unsigned long)(CYCLES_DIV * 1000 / (1000 + currprefs.m68k_speed_throttle));
		} else if (currprefs.m68k_speed_throttle > 0) {
			cycles_mult = (unsigned long)(CYCLES_DIV * 1000 / (1000 + currprefs.m68k_speed_throttle));
		}
	}
	if (currprefs.m68k_speed == 0 && currprefs.cpu_model >= 68020) {
		if (!cycles_mult)
			cycles_mult = CYCLES_DIV / 4;
		else
			cycles_mult /= 4;
	}

	currprefs.cpu_clock_multiplier = changed_prefs.cpu_clock_multiplier;
	currprefs.cpu_frequency = changed_prefs.cpu_frequency;

	baseclock = (currprefs.ntscmode ? CHIPSET_CLOCK_NTSC : CHIPSET_CLOCK_PAL) * 8;
	cpucycleunit = CYCLE_UNIT / 2;
	if (currprefs.cpu_clock_multiplier) {
		if (currprefs.cpu_clock_multiplier >= 256) {
			cpucycleunit = CYCLE_UNIT / (currprefs.cpu_clock_multiplier >> 8);
		} else {
			cpucycleunit = CYCLE_UNIT * currprefs.cpu_clock_multiplier;
		}
	} else if (currprefs.cpu_frequency) {
		cpucycleunit = CYCLE_UNIT * baseclock / currprefs.cpu_frequency;
	}
	if (cpucycleunit < 1)
		cpucycleunit = 1;
	if (currprefs.cpu_cycle_exact)
		write_log (_T("CPU cycleunit: %d (%.3f)\n"), cpucycleunit, (float)cpucycleunit / CYCLE_UNIT);
	config_changed = 1;
}
