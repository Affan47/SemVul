shutdown_uinput(void) {
#ifdef UINPUT_OK
	if (fd >= 0) {
		if (db) {
			rfbLog("shutdown_uinput called on fd=%d\n", fd);
		}
		ioctl(fd, UI_DEV_DESTROY);
		close(fd);
		fd = -1;
	}


	if (direct_rel_fd >= 0) close(direct_rel_fd);
	if (direct_abs_fd >= 0) close(direct_abs_fd);
	if (direct_btn_fd >= 0) close(direct_btn_fd);
	if (direct_key_fd >= 0) close(direct_key_fd);
	direct_rel_fd = -1;
	direct_abs_fd = -1;
	direct_btn_fd = -1;
	direct_key_fd = -1;
#endif
}
