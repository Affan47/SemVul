mc13xxx_regulator_enable(struct regulator_dev *rdev)
{
	struct mc13xxx_regulator_priv *priv = rdev_get_drvdata(rdev);
	struct mc13xxx_regulator *mc13xxx_regulators = priv->mc13xxx_regulators;
	int id = rdev_get_id(rdev);

	dev_dbg(rdev_get_dev(rdev), "%s id: %d\n", __func__, id);

	return mc13xxx_reg_rmw(priv->mc13xxx, mc13xxx_regulators[id].reg,
			       mc13xxx_regulators[id].enable_bit,
			       mc13xxx_regulators[id].enable_bit);
}
