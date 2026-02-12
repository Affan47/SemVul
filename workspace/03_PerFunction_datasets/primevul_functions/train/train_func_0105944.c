void change_console(struct vc_data *new_vc)
{
	struct vc_data *vc;

	if (!new_vc || new_vc->vc_num == fg_console || vt_dont_switch)
		return;


	vc = vc_cons[fg_console].d;
	if (vc->vt_mode.mode == VT_PROCESS) {


		vc->vt_newvt = new_vc->vc_num;
		if (kill_pid(vc->vt_pid, vc->vt_mode.relsig, 1) == 0) {


			return;
		}


		reset_vc(vc);


	}


	if (vc->vc_mode == KD_GRAPHICS)
		return;

	complete_change_console(new_vc);
}
