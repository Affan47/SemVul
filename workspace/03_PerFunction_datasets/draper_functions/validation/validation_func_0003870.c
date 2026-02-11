sound_ipc_callback(IPC_CMD_PARMS) {
	soundcontrol_ipc_frame *f;

	if (parent)
		return 0;

	if (len < (int) sizeof(soundcontrol_ipc_frame)) {
		_MSG("IPC sound handler got a short sound message", MSGFLAG_ERROR);
		return 0;
	}

	f = (soundcontrol_ipc_frame *) data;


	if (time(0) - f->timestamp > 2)
		return 0;

	int ret = ((SoundControl *) auxptr)->LocalPlay(f->player, f->msg);

	if (ret < 0)
		return -1;

	return 0;
}
