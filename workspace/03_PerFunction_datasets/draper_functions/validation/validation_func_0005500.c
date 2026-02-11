service_complete(struct connman_service *service)
{
	reply_pending(service, EIO);

	if (service->userconnect == FALSE)
		__connman_service_auto_connect();

	g_get_current_time(&service->modified);
	service_save(service);
}
