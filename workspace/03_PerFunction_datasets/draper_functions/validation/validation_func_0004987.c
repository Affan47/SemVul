cafe_smbus_read_done(struct mcam_camera *mcam)
{
	unsigned long flags;
	int c1;


	udelay(20);
	spin_lock_irqsave(&mcam->dev_lock, flags);
	c1 = mcam_reg_read(mcam, REG_TWSIC1);
	spin_unlock_irqrestore(&mcam->dev_lock, flags);
	return c1 & (TWSIC1_RVALID|TWSIC1_ERROR);
}
