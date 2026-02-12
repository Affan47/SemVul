enslave( struct net_device  *dev,  struct net_device  *slave_dev )
{
	struct net_local  *nl  = (struct net_local *) dev->priv;
	struct net_local  *snl = (struct net_local *) slave_dev->priv;

	if( nl->state & FL_SLAVE )
		return  -EBUSY;

	if( snl->state & FL_SLAVE )
		return  -EBUSY;

	spin_lock( &nl->lock );
	spin_lock( &snl->lock );


	snl->link = nl->link;
	nl->link  = slave_dev;
	snl->master = dev;
	snl->state |= FL_SLAVE;


	memset( &snl->stats, 0, sizeof(struct net_device_stats) );
	netif_stop_queue( slave_dev );
	netif_wake_queue( dev );

	spin_unlock( &snl->lock );
	spin_unlock( &nl->lock );
	printk( KERN_NOTICE "%s: slave device (%s) attached.\n",
		dev->name, slave_dev->name );
	return  0;
}
