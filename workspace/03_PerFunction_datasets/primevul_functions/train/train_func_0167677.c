static void b43_bcma_phy_reset(struct b43_wldev *dev)
{
	u32 flags;


	flags = bcma_aread32(dev->dev->bdev, BCMA_IOCTL);
	flags |= B43_BCMA_IOCTL_PHY_RESET;
	flags |= B43_BCMA_IOCTL_PHY_BW_20MHZ;
	bcma_awrite32(dev->dev->bdev, BCMA_IOCTL, flags);
	udelay(2);


	flags = bcma_aread32(dev->dev->bdev, BCMA_IOCTL);
	flags &= ~B43_BCMA_IOCTL_PHY_RESET;
	flags |= BCMA_IOCTL_FGC;
	bcma_awrite32(dev->dev->bdev, BCMA_IOCTL, flags);
	udelay(1);


	flags = bcma_aread32(dev->dev->bdev, BCMA_IOCTL);
	flags &= ~BCMA_IOCTL_FGC;
	bcma_awrite32(dev->dev->bdev, BCMA_IOCTL, flags);
	udelay(1);
}
