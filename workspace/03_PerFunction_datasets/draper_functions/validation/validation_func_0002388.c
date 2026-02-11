ib_mcast_detach ( struct ib_device *ibdev, struct ib_queue_pair *qp,
		       union ib_gid *gid ) {
	struct ib_multicast_gid *mgid;


	ibdev->op->mcast_detach ( ibdev, qp, gid );


	list_for_each_entry ( mgid, &qp->mgids, list ) {
		if ( memcmp ( &mgid->gid, gid, sizeof ( mgid->gid ) ) == 0 ) {
			list_del ( &mgid->list );
			free ( mgid );
			break;
		}
	}
}
