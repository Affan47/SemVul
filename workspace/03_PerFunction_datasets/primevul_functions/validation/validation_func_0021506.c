static int __init sbni_init(struct net_device *dev)
{
	int  i;
	if( dev->base_addr )
		return  sbni_isa_probe( dev );


	if( io[ num ] != -1 )
		dev->base_addr	= io[ num ],
		dev->irq	= irq[ num ];
	else if( scandone  ||  io[ 0 ] != -1 )
		return  -ENODEV;


	if( dev->base_addr )
		return  sbni_isa_probe( dev );


	if( !skip_pci_probe  &&  !sbni_pci_probe( dev ) )
		return  0;

	if( io[ num ] == -1 ) {

		scandone = 1;
		if( num > 0 )
			return  -ENODEV;
	}

	for( i = 0;  netcard_portlist[ i ];  ++i ) {
		int  ioaddr = netcard_portlist[ i ];
		if( request_region( ioaddr, SBNI_IO_EXTENT, dev->name )
		    &&  sbni_probe1( dev, ioaddr, 0 ))
			return 0;
	}

	return  -ENODEV;
}
