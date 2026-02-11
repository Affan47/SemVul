arcam_av_server_stop(pthread_t thread, const char* port)
{
	int client_fd = arcam_av_client(port);
	if (client_fd < 0)
		return -1;

	if (send(client_fd, &thread, sizeof(pthread_t), 0) > 0)
		pthread_join(thread, NULL);

	close(client_fd);
	return 0;
}
