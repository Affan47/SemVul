find_netdev_by_location ( unsigned int bus_type,
					      unsigned int location ) {
	struct net_device *netdev;

	list_for_each_entry ( netdev, &net_devices, list ) {
		if ( ( netdev->dev->desc.bus_type == bus_type ) &&
		     ( netdev->dev->desc.location == location ) )
			return netdev;
	}

	return NULL;
}
