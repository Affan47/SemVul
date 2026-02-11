sis900_read_mode(struct nic *nic __unused, int phy_addr, int *speed, int *duplex)
{
    int i = 0;
    u32 status;
    u16 phy_id0, phy_id1;


    do {
        status = sis900_mdio_read(phy_addr, MII_STSOUT);
    } while (i++ < 2);

    *speed = HW_SPEED_10_MBPS;
    *duplex = FDX_CAPABLE_HALF_SELECTED;

    if (status & (MII_NWAY_TX | MII_NWAY_TX_FDX))
	*speed = HW_SPEED_100_MBPS;
    if (status & ( MII_NWAY_TX_FDX | MII_NWAY_T_FDX))
	*duplex = FDX_CAPABLE_FULL_SELECTED;


    phy_id0 = sis900_mdio_read(phy_addr, MII_PHY_ID0);
    phy_id1 = sis900_mdio_read(phy_addr, MII_PHY_ID1);
    if((phy_id0 == 0x0000) && ((phy_id1 & 0xFFF0) == 0x8200)){
	if(sis900_mdio_read(phy_addr, MII_CONTROL) & MII_CNTL_FDX)
	    *duplex = FDX_CAPABLE_FULL_SELECTED;
	if(sis900_mdio_read(phy_addr, 0x0019) & 0x01)
	    *speed = HW_SPEED_100_MBPS;
    }

    if (status & MII_STSOUT_LINK_FAIL)
        printf("sis900_read_mode: Media Link Off\n");
    else
        printf("sis900_read_mode: Media Link On %s %s-duplex \n",
               *speed == HW_SPEED_100_MBPS ?
               "100mbps" : "10mbps",
               *duplex == FDX_CAPABLE_FULL_SELECTED ?
               "full" : "half");
}
