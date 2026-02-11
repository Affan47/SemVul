e1000_configure_rx ( struct e1000_adapter *adapter )
{
	struct e1000_hw *hw = &adapter->hw;
	uint32_t rctl;

	DBG ( "e1000_configure_rx\n" );


	rctl = E1000_READ_REG ( hw, E1000_RCTL );
	E1000_WRITE_REG ( hw, E1000_RCTL, rctl & ~E1000_RCTL_EN );
	E1000_WRITE_FLUSH ( hw );
	mdelay(10);

	adapter->rx_curr = 0;


	E1000_WRITE_REG ( hw, E1000_RDBAL(0), virt_to_bus ( adapter->rx_base ) );
	E1000_WRITE_REG ( hw, E1000_RDBAH(0), 0 );
	E1000_WRITE_REG ( hw, E1000_RDLEN(0), adapter->rx_ring_size );

	E1000_WRITE_REG ( hw, E1000_RDH(0), 0 );
	E1000_WRITE_REG ( hw, E1000_RDT(0), NUM_RX_DESC - 1 );


	rctl |=  E1000_RCTL_EN | E1000_RCTL_BAM | E1000_RCTL_SZ_2048 |
		 E1000_RCTL_MPE | E1000_RCTL_SECRC;
	E1000_WRITE_REG ( hw, E1000_RCTL, rctl );
	E1000_WRITE_FLUSH ( hw );

        DBG ( "E1000_RDBAL(0): %#08x\n",  E1000_READ_REG ( hw, E1000_RDBAL(0) ) );
        DBG ( "E1000_RDLEN(0): %d\n",     E1000_READ_REG ( hw, E1000_RDLEN(0) ) );
        DBG ( "E1000_RCTL:  %#08x\n",  E1000_READ_REG ( hw, E1000_RCTL ) );
}
