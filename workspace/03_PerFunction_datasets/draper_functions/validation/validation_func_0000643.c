ixgb_get_ee_device_id(struct ixgb_hw *hw)
{
	struct ixgb_ee_map_type *ee_map = (struct ixgb_ee_map_type *)hw->eeprom;

	if (ixgb_check_and_get_eeprom_data(hw))
		return le16_to_cpu(ee_map->device_id);

	return 0;
}
