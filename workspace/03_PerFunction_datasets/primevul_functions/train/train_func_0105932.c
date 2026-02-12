static void complete_change_console(struct vc_data *vc)
{
	unsigned char old_vc_mode;
	int old = fg_console;

	last_console = fg_console;


	old_vc_mode = vc_cons[fg_console].d->vc_mode;
	switch_screen(vc);


	if (old_vc_mode != vc->vc_mode) {
		if (vc->vc_mode == KD_TEXT)
			do_unblank_screen(1);
		else
			do_blank_screen(1);
	}


	if (vc->vt_mode.mode == VT_PROCESS) {


		if (kill_pid(vc->vt_pid, vc->vt_mode.acqsig, 1) != 0) {


			reset_vc(vc);

			if (old_vc_mode != vc->vc_mode) {
				if (vc->vc_mode == KD_TEXT)
					do_unblank_screen(1);
				else
					do_blank_screen(1);
			}
		}
	}


	vt_event_post(VT_EVENT_SWITCH, old, vc->vc_num);
	return;
}
