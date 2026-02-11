zatm_phy_put(struct atm_dev *dev,unsigned char value,
    unsigned long addr)
{
	struct zatm_dev *zatm_dev;

	zatm_dev = ZATM_DEV(dev);
	zwait;
	zout(value,CER);
	zout(uPD98401_IND_ACC | uPD98401_IA_B0 |
	    (uPD98401_IA_TGT_PHY << uPD98401_IA_TGT_SHIFT) | addr,CMR);
}
