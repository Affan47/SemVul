reefnet_sensusultra_device_dump (dc_device_t *abstract, dc_buffer_t *buffer)
{
	reefnet_sensusultra_device_t *device = (reefnet_sensusultra_device_t*) abstract;


	if (!dc_buffer_clear (buffer) || !dc_buffer_reserve (buffer, SZ_MEMORY)) {
		ERROR (abstract->context, "Insufficient buffer space available.");
		return DC_STATUS_NOMEMORY;
	}


	dc_event_progress_t progress = EVENT_PROGRESS_INITIALIZER;
	progress.maximum = SZ_MEMORY;
	device_event_emit (abstract, DC_EVENT_PROGRESS, &progress);


	dc_status_t rc = reefnet_sensusultra_send (device, 0xB421);
	if (rc != DC_STATUS_SUCCESS)
		return rc;

	unsigned int nbytes = 0;
	unsigned int npages = 0;
	while (nbytes < SZ_MEMORY) {

		unsigned char packet[SZ_PACKET + 4] = {0};
		rc = reefnet_sensusultra_page (device, packet, sizeof (packet), npages);
		if (rc != DC_STATUS_SUCCESS)
			return rc;


		progress.current += SZ_PACKET;
		device_event_emit (abstract, DC_EVENT_PROGRESS, &progress);


		if (!dc_buffer_prepend (buffer, packet + 2, SZ_PACKET)) {
			ERROR (abstract->context, "Insufficient buffer space available.");
			return DC_STATUS_NOMEMORY;
		}


		rc = reefnet_sensusultra_send_uchar (device, ACCEPT);
		if (rc != DC_STATUS_SUCCESS)
			return rc;

		nbytes += SZ_PACKET;
		npages++;
	}

	return DC_STATUS_SUCCESS;
}
