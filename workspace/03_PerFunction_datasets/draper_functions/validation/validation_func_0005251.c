hiface_pcm_stream_stop(struct pcm_runtime *rt)
{
	int i, time;

	if (rt->stream_state != STREAM_DISABLED) {
		rt->stream_state = STREAM_STOPPING;

		for (i = 0; i < PCM_N_URBS; i++) {
			time = usb_wait_anchor_empty_timeout(
					&rt->out_urbs[i].submitted, 100);
			if (!time)
				usb_kill_anchored_urbs(
					&rt->out_urbs[i].submitted);
			usb_kill_urb(&rt->out_urbs[i].instance);
		}

		rt->stream_state = STREAM_DISABLED;
	}
}
