handle_channel( struct net_device  *dev )
{
	struct net_local	*nl    = (struct net_local *) dev->priv;
	unsigned long		ioaddr = dev->base_addr;

	int  req_ans;
	unsigned char  csr0;

#ifdef CONFIG_SBNI_MULTILINE

	if( nl->state & FL_SLAVE )
		spin_lock( &((struct net_local *) nl->master->priv)->lock );
#endif

	outb( (inb( ioaddr + CSR0 ) & ~EN_INT) | TR_REQ, ioaddr + CSR0 );

	nl->timer_ticks = CHANGE_LEVEL_START_TICKS;
	for(;;) {
		csr0 = inb( ioaddr + CSR0 );
		if( ( csr0 & (RC_RDY | TR_RDY) ) == 0 )
			break;

		req_ans = !(nl->state & FL_PREV_OK);

		if( csr0 & RC_RDY )
			req_ans = recv_frame( dev );


		csr0 = inb( ioaddr + CSR0 );
		if( !(csr0 & TR_RDY)  ||  (csr0 & RC_RDY) )
			printk( KERN_ERR "%s: internal error!\n", dev->name );


		if( req_ans  ||  nl->tx_frameno != 0 )
			send_frame( dev );
		else

			outb( inb( ioaddr + CSR0 ) & ~TR_REQ, ioaddr + CSR0 );
	}

	outb( inb( ioaddr + CSR0 ) | EN_INT, ioaddr + CSR0 );

#ifdef CONFIG_SBNI_MULTILINE
	if( nl->state & FL_SLAVE )
		spin_unlock( &((struct net_local *) nl->master->priv)->lock );
#endif
}
