spmi_regulator_select_voltage(struct spmi_regulator *vreg,
		int min_uV, int max_uV, u8 *range_sel, u8 *voltage_sel,
		unsigned *selector)
{
	const struct spmi_voltage_range *range;
	int uV = min_uV;
	int lim_min_uV, lim_max_uV, i, range_id, range_max_uV;


	lim_min_uV = vreg->set_points->range[0].set_point_min_uV;
	lim_max_uV =
	  vreg->set_points->range[vreg->set_points->count - 1].set_point_max_uV;

	if (uV < lim_min_uV && max_uV >= lim_min_uV)
		uV = lim_min_uV;

	if (uV < lim_min_uV || uV > lim_max_uV) {
		dev_err(vreg->dev,
			"request v=[%d, %d] is outside possible v=[%d, %d]\n",
			 min_uV, max_uV, lim_min_uV, lim_max_uV);
		return -EINVAL;
	}


	for (i = vreg->set_points->count - 1; i > 0; i--) {
		range_max_uV = vreg->set_points->range[i - 1].set_point_max_uV;
		if (uV > range_max_uV && range_max_uV > 0)
			break;
	}

	range_id = i;
	range = &vreg->set_points->range[range_id];
	*range_sel = range->range_sel;


	*voltage_sel = DIV_ROUND_UP(uV - range->min_uV, range->step_uV);
	uV = *voltage_sel * range->step_uV + range->min_uV;

	if (uV > max_uV) {
		dev_err(vreg->dev,
			"request v=[%d, %d] cannot be met by any set point; "
			"next set point: %d\n",
			min_uV, max_uV, uV);
		return -EINVAL;
	}

	*selector = 0;
	for (i = 0; i < range_id; i++)
		*selector += vreg->set_points->range[i].n_voltages;
	*selector += (uV - range->set_point_min_uV) / range->step_uV;

	return 0;
}
