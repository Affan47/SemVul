rtl_spi_read_bit ( struct bit_basher *basher,
			      unsigned int bit_id ) {
	struct rtl8139_nic *rtl = container_of ( basher, struct rtl8139_nic,
						 spibit.basher );
	uint8_t mask = rtl_ee_bits[bit_id];
	uint8_t eereg;

	eereg = inb ( rtl->ioaddr + Cfg9346 );
	return ( eereg & mask );
}
