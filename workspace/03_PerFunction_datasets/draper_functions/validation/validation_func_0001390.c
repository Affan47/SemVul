eisa_probe ( struct eisa_device *eisa ) {
	struct eisa_driver *driver;
	struct eisa_device_id *id;
	unsigned int i;
	int rc;

	DBG ( "Adding EISA device %02x (%04x:%04x (\"%s\") io %x)\n",
	      eisa->slot, eisa->vendor_id, eisa->prod_id,
	      isa_id_string ( eisa->vendor_id, eisa->prod_id ), eisa->ioaddr );

	for_each_table_entry ( driver, EISA_DRIVERS ) {
		for ( i = 0 ; i < driver->id_count ; i++ ) {
			id = &driver->ids[i];
			if ( id->vendor_id != eisa->vendor_id )
				continue;
			if ( ISA_PROD_ID ( id->prod_id ) !=
			     ISA_PROD_ID ( eisa->prod_id ) )
				continue;
			eisa->driver = driver;
			eisa->dev.driver_name = id->name;
			DBG ( "...using driver %s\n", eisa->dev.driver_name );
			if ( ( rc = driver->probe ( eisa, id ) ) != 0 ) {
				DBG ( "......probe failed\n" );
				continue;
			}
			return 0;
		}
	}

	DBG ( "...no driver found\n" );
	return -ENOTTY;
}
