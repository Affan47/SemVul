it8709_wait(struct ite_dev *dev)
{
	int i = 0;


	for (i = 0; i < 15000; i++) {
		udelay(2);
		if (it8709_rm(dev, IT8709_MODE) == IT8709_IDLE)
			break;
	}
}
