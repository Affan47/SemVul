jack_unregister_server (const char *server_name )
{
	int i;
	pid_t my_pid = getpid ();

	jack_shm_lock_registry ();

	for (i = 0; i < MAX_SERVERS; i++) {
		if (jack_shm_header->server[i].pid == my_pid) {
			memset (&jack_shm_header->server[i], 0,
				sizeof (jack_shm_server_t));
		}
	}

	jack_shm_unlock_registry ();
}
