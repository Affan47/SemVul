initialize_xrecord(void) {
	use_xrecord = 0;
	if (! xrecord_present) {
		return;
	}
	if (nofb) {
		return;
	}
	if (noxrecord) {
		return;
	}
	if (remote_direct) {
		return;
	}
	RAWFB_RET_VOID
#if LIBVNCSERVER_HAVE_RECORD

	if (rr_CA) XFree_wr(rr_CA);
	if (rr_CW) XFree_wr(rr_CW);
	if (rr_GS) XFree_wr(rr_GS);

	rr_CA = XRecordAllocRange();
	rr_CW = XRecordAllocRange();
	rr_GS = XRecordAllocRange();
	if (!rr_CA || !rr_CW || !rr_GS) {
		return;
	}

	rr_CA->core_requests.first = X_CopyArea;
	rr_CA->core_requests.last  = X_CopyArea;

	rr_CW->core_requests.first = X_ConfigureWindow;
	rr_CW->core_requests.last  = X_ConfigureWindow;

	rr_GS->core_requests.first = X_GrabServer;
	rr_GS->core_requests.last  = X_UngrabServer;

	X_LOCK;

	if (rdpy_data) {
		XCloseDisplay_wr(rdpy_data);
		rdpy_data = NULL;
	}
	if (rdpy_ctrl) {
		XCloseDisplay_wr(rdpy_ctrl);
		rdpy_ctrl = NULL;
	}
	rdpy_ctrl = XOpenDisplay_wr(DisplayString(dpy));
	if (!rdpy_ctrl) {
		fprintf(stderr, "rdpy_ctrl open failed: %s / %s / %s / %s\n", getenv("DISPLAY"), DisplayString(dpy), getenv("XAUTHORITY"), getenv("XAUTHORIT_"));
	}
	XSync(dpy, True);
	XSync(rdpy_ctrl, True);

	rdpy_data = XOpenDisplay_wr(DisplayString(dpy));
	if (!rdpy_data) {
		fprintf(stderr, "rdpy_data open failed\n");
	}
	if (!rdpy_ctrl || ! rdpy_data) {
		X_UNLOCK;
		return;
	}
	disable_grabserver(rdpy_ctrl, 0);
	disable_grabserver(rdpy_data, 0);

	use_xrecord = 1;


	if (gdpy_data) {
		XCloseDisplay_wr(gdpy_data);
		gdpy_data = NULL;
	}
	if (gdpy_ctrl) {
		XCloseDisplay_wr(gdpy_ctrl);
		gdpy_ctrl = NULL;
	}
	xserver_grabbed = 0;

	gdpy_ctrl = XOpenDisplay_wr(DisplayString(dpy));
	if (!gdpy_ctrl) {
		fprintf(stderr, "gdpy_ctrl open failed\n");
	}
	XSync(dpy, True);
	XSync(gdpy_ctrl, True);
	gdpy_data = XOpenDisplay_wr(DisplayString(dpy));
	if (!gdpy_data) {
		fprintf(stderr, "gdpy_data open failed\n");
	}
	if (gdpy_ctrl && gdpy_data) {
		disable_grabserver(gdpy_ctrl, 0);
		disable_grabserver(gdpy_data, 0);
		xrecord_grabserver(1);
	}
	X_UNLOCK;
#endif
}
