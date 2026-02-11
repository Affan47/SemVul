regmap_precious(struct regmap *map, unsigned int reg)
{
	if (!regmap_readable(map, reg))
		return false;

	if (map->precious_reg)
		return map->precious_reg(map->dev, reg);

	if (map->precious_table)
		return regmap_check_range_table(map, reg, map->precious_table);

	return false;
}
