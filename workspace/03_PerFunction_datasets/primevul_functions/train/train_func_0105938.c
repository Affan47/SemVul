static int vt_reldisp(struct vc_data *vc, unsigned int swtch)
{
	int newvt, ret;

	if (vc->vt_mode.mode != VT_PROCESS)
		return -EINVAL;


	if (vc->vt_newvt < 0) {

		return swtch == VT_ACKACQ ? 0 : -EINVAL;
	}


	if (swtch == 0) {

		vc->vt_newvt = -1;
		return 0;
	}


	newvt = vc->vt_newvt;
	vc->vt_newvt = -1;
	ret = vc_allocate(newvt);
	if (ret)
		return ret;


	complete_change_console(vc_cons[newvt].d);

	return 0;
}
