radio_mute(int fd, int mute, int alsa_loopback)
{
    struct v4l2_control ctrl;
    int res;

    memset (&ctrl, 0, sizeof(ctrl));
    ctrl.id = V4L2_CID_AUDIO_MUTE;
    ctrl.value = mute;

    res = ioctl(fd, VIDIOC_S_CTRL, &ctrl);
    if (res == -1 && errno != EINVAL && errno != ENOTTY)
	perror("VIDIOC_S_CTRL");

#if defined(HAVE_ALSA)
    if (alsa_loopback) {
	if (mute)
	    alsa_thread_stop();
	else
	    alsa_thread_startup(alsa_playback, alsa_capture,
				alsa_latency, stderr, debug);
    }
#endif
}
