static void tnt_event_hook(struct gps_device_t *session, event_t event)

{
    if (session->context->readonly)
	return;
    if (event == event_wakeup) {
	(void)tnt_send(session, "@F0.3=1");
	(void)tnt_send(session, "@F2.2=1");
    }
}
