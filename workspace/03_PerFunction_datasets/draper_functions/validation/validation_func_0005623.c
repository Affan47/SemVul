ltc3589_parse_regulators_dt(struct ltc3589 *ltc3589)
{
	struct device *dev = ltc3589->dev;
	struct device_node *node;
	int i, ret;

	node = of_get_child_by_name(dev->of_node, "regulators");
	if (!node) {
		dev_err(dev, "regulators node not found\n");
		return -EINVAL;
	}

	ret = of_regulator_match(dev, node, ltc3589_matches,
				 ARRAY_SIZE(ltc3589_matches));
	of_node_put(node);
	if (ret < 0) {
		dev_err(dev, "Error parsing regulator init data: %d\n", ret);
		return ret;
	}
	if (ret != LTC3589_NUM_REGULATORS) {
		dev_err(dev, "Only %d regulators described in device tree\n",
			ret);
		return -EINVAL;
	}


	for (i = 0; i < LTC3589_LDO3; i++) {
		struct ltc3589_regulator *desc = &ltc3589->regulator_descs[i];
		struct device_node *np = ltc3589_matches[i].of_node;
		u32 vdiv[2];

		ret = of_property_read_u32_array(np, "lltc,fb-voltage-divider",
						 vdiv, 2);
		if (ret) {
			dev_err(dev, "Failed to parse voltage divider: %d\n",
				ret);
			return ret;
		}

		desc->r1 = vdiv[0];
		desc->r2 = vdiv[1];
	}

	return 0;
}
