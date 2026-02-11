bcm590xx_get_vsel_register(int id)
{
	if (BCM590XX_REG_IS_LDO(id))
		return BCM590XX_RFLDOCTRL + id;
	else if (BCM590XX_REG_IS_GPLDO(id))
		return BCM590XX_GPLDO1CTRL + id;
	else
		return BCM590XX_CSRVOUT1 + (id - BCM590XX_REG_CSR) * 3;
}
