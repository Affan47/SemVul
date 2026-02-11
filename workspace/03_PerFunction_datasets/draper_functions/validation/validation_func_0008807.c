hermon_eth_complete_recv ( struct ib_device *ibdev __unused,
				       struct ib_queue_pair *qp,
				       struct ib_address_vector *av,
				       struct io_buffer *iobuf, int rc ) {
	struct net_device *netdev = ib_qp_get_ownerdata ( qp );
	struct net_device *vlan;


	if ( av->vlan_present ) {
		if ( ( vlan = vlan_find ( netdev, av->vlan ) ) != NULL ) {
			netdev = vlan;
		} else if ( rc == 0 ) {
			rc = -ENODEV;
		}
	}


	if ( rc == 0 ) {
		netdev_rx ( netdev, iobuf );
	} else {
		netdev_rx_err ( netdev, iobuf, rc );
	}
}
