static void oceanserver_event_hook(struct gps_device_t *session,
				   event_t event)
{
    if (session->context->readonly)
	return;
    if (event == event_configure && session->packet.counter == 0) {

	(void)oceanserver_send(session->gpsdata.gps_fd, "2\n");

	(void)oceanserver_send(session->gpsdata.gps_fd, "X2047");
    }
}
