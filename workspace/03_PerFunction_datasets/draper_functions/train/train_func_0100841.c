type3_infoblock(struct net_device *dev, u_char count, u_char *p)
{
    struct de4x5_private *lp = netdev_priv(dev);
    u_char len = (*p & BLOCK_LEN)+1;


    if (--count > lp->tcount) {
	if (*(p+len) < 128) {
	    return dc_infoblock[COMPACT](dev, count, p+len);
	} else {
	    return dc_infoblock[*(p+len+1)](dev, count, p+len);
	}
    }

    p += 2;
    if (lp->state == INITIALISED) {
        lp->ibn = 3;
        lp->active = *p++;
	if (MOTO_SROM_BUG) lp->active = 0;
	lp->phy[lp->active].gep = (*p ? p : NULL); p += (2 * (*p) + 1);
	lp->phy[lp->active].rst = (*p ? p : NULL); p += (2 * (*p) + 1);
	lp->phy[lp->active].mc  = get_unaligned_le16(p); p += 2;
	lp->phy[lp->active].ana = get_unaligned_le16(p); p += 2;
	lp->phy[lp->active].fdx = get_unaligned_le16(p); p += 2;
	lp->phy[lp->active].ttm = get_unaligned_le16(p); p += 2;
	lp->phy[lp->active].mci = *p;
	return 0;
    } else if ((lp->media == INIT) && (lp->timeout < 0)) {
        lp->ibn = 3;
	lp->active = *p;
	if (MOTO_SROM_BUG) lp->active = 0;
	lp->infoblock_csr6 = OMR_MII_100;
	lp->useMII = true;
	lp->infoblock_media = ANS;

	de4x5_switch_mac_port(dev);
    }

    return dc2114x_autoconf(dev);
}
