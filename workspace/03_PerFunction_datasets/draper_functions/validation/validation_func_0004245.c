srp_open ( struct interface *block, struct interface *socket,
	       union srp_port_id *initiator, union srp_port_id *target,
	       uint32_t memory_handle, struct scsi_lun *lun ) {
	struct srp_device *srpdev;
	int tag;
	int rc;


	srpdev = zalloc ( sizeof ( *srpdev ) );
	if ( ! srpdev ) {
		rc = -ENOMEM;
		goto err_zalloc;
	}
	ref_init ( &srpdev->refcnt, NULL );
	intf_init ( &srpdev->scsi, &srpdev_scsi_desc, &srpdev->refcnt );
	intf_init ( &srpdev->socket, &srpdev_socket_desc, &srpdev->refcnt );
	INIT_LIST_HEAD ( &srpdev->commands );
	srpdev->memory_handle = memory_handle;
	DBGC ( srpdev, "SRP %p %08x%08x%08x%08x->%08x%08x%08x%08x\n", srpdev,
	       ntohl ( initiator->dwords[0] ), ntohl ( initiator->dwords[1] ),
	       ntohl ( initiator->dwords[2] ), ntohl ( initiator->dwords[3] ),
	       ntohl ( target->dwords[0] ), ntohl ( target->dwords[1] ),
	       ntohl ( target->dwords[2] ), ntohl ( target->dwords[3] ) );


	memcpy ( &srpdev->initiator, initiator, sizeof ( srpdev->initiator ) );
	memcpy ( &srpdev->target, target, sizeof ( srpdev->target ) );
	memcpy ( &srpdev->lun, lun, sizeof ( srpdev->lun ) );


	intf_plug_plug ( &srpdev->socket, socket );
	tag = srp_new_tag ( srpdev );
	assert ( tag >= 0 );
	if ( ( rc = srp_login ( srpdev, initiator, target, tag ) ) != 0 )
		goto err_login;


	if ( ( rc = scsi_open ( block, &srpdev->scsi, lun ) ) != 0 ) {
		DBGC ( srpdev, "SRP %p could not create SCSI device: %s\n",
		       srpdev, strerror ( rc ) );
		goto err_scsi_open;
	}


	ref_put ( &srpdev->refcnt );
	return 0;

 err_scsi_open:
 err_login:
	srpdev_close ( srpdev, rc );
	ref_put ( &srpdev->refcnt );
 err_zalloc:
	return rc;
}
