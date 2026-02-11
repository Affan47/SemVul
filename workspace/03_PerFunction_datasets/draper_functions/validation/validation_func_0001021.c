resetwarning_do (int canreset)
{
	if (resetwarning_phase) {

		if (canreset) {
			resetwarning_phase = 0;
			resetwarning_timer = 0;
		}
		return 0;
	}
	resetwarning_phase = 1;
	resetwarning_timer = maxvpos_nom * 5;
	write_log (_T("KB: reset warning triggered\n"));
	sendrw ();
	return 1;
}
