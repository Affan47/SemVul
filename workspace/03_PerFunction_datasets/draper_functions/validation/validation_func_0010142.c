multiplexed_add_or_remove(struct multiplexed_thread *multiplexed_thread, struct ast_channel *chan, int add)
{
	int i, removed = 0;
	pthread_t thread = AST_PTHREADT_NULL;

	ao2_lock(multiplexed_thread);

	multiplexed_nudge(multiplexed_thread);

	for (i = 0; i < MULTIPLEXED_MAX_CHANNELS; i++) {
		if (multiplexed_thread->chans[i] == chan) {
			if (!add) {
				multiplexed_thread->chans[i] = NULL;
				multiplexed_thread->service_count--;
				removed = 1;
			}
			break;
		} else if (!multiplexed_thread->chans[i] && add) {
			multiplexed_thread->chans[i] = chan;
			multiplexed_thread->service_count++;
			break;
		}
	}

	if (multiplexed_thread->service_count && multiplexed_thread->thread == AST_PTHREADT_NULL) {
		ao2_ref(multiplexed_thread, +1);
		if (ast_pthread_create(&multiplexed_thread->thread, NULL, multiplexed_thread_function, multiplexed_thread)) {
			ao2_ref(multiplexed_thread, -1);
			ast_debug(1, "Failed to create an actual thread for multiplexed thread '%p', trying next time\n", multiplexed_thread);
		}
	} else if (!multiplexed_thread->service_count && multiplexed_thread->thread != AST_PTHREADT_NULL) {
		thread = multiplexed_thread->thread;
		multiplexed_thread->thread = AST_PTHREADT_STOP;
	} else if (!add && removed) {
		memmove(multiplexed_thread->chans + i, multiplexed_thread->chans + i + 1, sizeof(struct ast_channel *) * (MULTIPLEXED_MAX_CHANNELS - (i + 1)));
	}

	ao2_unlock(multiplexed_thread);

	if (thread != AST_PTHREADT_NULL) {
		pthread_join(thread, NULL);
	}

	return;
}
