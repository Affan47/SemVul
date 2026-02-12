sbni_open( struct net_device  *dev )
{
	struct net_local	*nl = (struct net_local *) dev->priv;
	struct timer_list	*w  = &nl->watchdog;


	if( dev->base_addr < 0x400 ) {
		struct net_device  **p = sbni_cards;
		for( ;  *p  &&  p < sbni_cards + SBNI_MAX_NUM_CARDS;  ++p )
			if( (*p)->irq == dev->irq
			    &&  ((*p)->base_addr == dev->base_addr + 4
				 ||  (*p)->base_addr == dev->base_addr - 4)
			    &&  (*p)->flags & IFF_UP ) {

				((struct net_local *) ((*p)->priv))
					->second = dev;
				printk( KERN_NOTICE "%s: using shared irq "
					"with %s\n", dev->name, (*p)->name );
				nl->state |= FL_SECONDARY;
				goto  handler_attached;
			}
	}

	if( request_irq(dev->irq, sbni_interrupt, IRQF_SHARED, dev->name, dev) ) {
		printk( KERN_ERR "%s: unable to get IRQ %d.\n",
			dev->name, dev->irq );
		return  -EAGAIN;
	}

handler_attached:

	spin_lock( &nl->lock );
	memset( &nl->stats, 0, sizeof(struct net_device_stats) );
	memset( &nl->in_stats, 0, sizeof(struct sbni_in_stats) );

	card_start( dev );

	netif_start_queue( dev );


	init_timer( w );
	w->expires	= jiffies + SBNI_TIMEOUT;
	w->data		= (unsigned long) dev;
	w->function	= sbni_watchdog;
	add_timer( w );

	spin_unlock( &nl->lock );
	return 0;
}
