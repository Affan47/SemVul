is_spd_100(struct net_device *dev)
{
    struct de4x5_private *lp = netdev_priv(dev);
    u_long iobase = dev->base_addr;
    int spd;

    if (lp->useMII) {
	spd = mii_rd(lp->phy[lp->active].spd.reg, lp->phy[lp->active].addr, DE4X5_MII);
	spd = ~(spd ^ lp->phy[lp->active].spd.value);
	spd &= lp->phy[lp->active].spd.mask;
    } else if (!lp->useSROM) {
	spd = ((~gep_rd(dev)) & GEP_SLNK);
    } else {
	if ((lp->ibn == 2) || !lp->asBitValid)
	    return (lp->chipset == DC21143) ? (~inl(DE4X5_SISR)&SISR_LS100) : 0;

	spd = (lp->asBitValid & (lp->asPolarity ^ (gep_rd(dev) & lp->asBit))) |
	          (lp->linkOK & ~lp->asBitValid);
    }

    return spd;
}
