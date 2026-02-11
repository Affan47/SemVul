fluid_mixer_thread_func (void* data)
{
	fluid_mixer_buffers_t* buffers = data;
	fluid_rvoice_mixer_t* mixer = buffers->mixer;
	int hasValidData = 0;
	FLUID_DECLARE_VLA(fluid_real_t*, bufs, buffers->buf_count*2 + buffers->fx_buf_count*2);
	int bufcount = 0;

	while (!fluid_atomic_int_get(&mixer->threads_should_terminate)) {
		fluid_rvoice_t* rvoice = fluid_mixer_get_mt_rvoice(mixer);
		if (rvoice == NULL) {

			fluid_atomic_int_set(&buffers->ready, hasValidData ? THREAD_BUF_VALID : THREAD_BUF_NODATA);
			fluid_cond_mutex_lock(mixer->thread_ready_m);
			fluid_cond_signal(mixer->thread_ready);
			fluid_cond_mutex_unlock(mixer->thread_ready_m);

			fluid_cond_mutex_lock(mixer->wakeup_threads_m);
			while (1) {
				int j = fluid_atomic_int_get(&buffers->ready);
				if (j == THREAD_BUF_PROCESSING || j == THREAD_BUF_TERMINATE)
					break;
				fluid_cond_wait(mixer->wakeup_threads, mixer->wakeup_threads_m);
			}
			fluid_cond_mutex_unlock(mixer->wakeup_threads_m);

			hasValidData = 0;
		} else {

			if (!hasValidData) {
				fluid_mixer_buffers_zero(buffers);
				bufcount = fluid_mixer_buffers_prepare(buffers, bufs);
				hasValidData = 1;
			}

			fluid_mixer_buffers_render_one(buffers, rvoice, bufs, bufcount);
		}
	}

}
