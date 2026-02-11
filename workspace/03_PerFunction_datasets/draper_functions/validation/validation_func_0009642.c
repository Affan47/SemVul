storvsc_device_configure(struct scsi_device *sdevice)
{

	blk_queue_bounce_limit(sdevice->request_queue, BLK_BOUNCE_ANY);

	blk_queue_rq_timeout(sdevice->request_queue, (storvsc_timeout * HZ));


	blk_queue_virt_boundary(sdevice->request_queue, PAGE_SIZE - 1);

	sdevice->no_write_same = 1;


	if (!strncmp(sdevice->vendor, "Msft", 4)) {
		switch (vmstor_proto_version) {
		case VMSTOR_PROTO_VERSION_WIN8:
		case VMSTOR_PROTO_VERSION_WIN8_1:
			sdevice->scsi_level = SCSI_SPC_3;
			break;
		}

		if (vmstor_proto_version >= VMSTOR_PROTO_VERSION_WIN10)
			sdevice->no_write_same = 0;
	}

	return 0;
}
