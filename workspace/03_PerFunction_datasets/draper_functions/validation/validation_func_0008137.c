skge_supported_modes(const struct skge_hw *hw)
{
	u32 supported;

	if (hw->copper) {
		supported = SUPPORTED_10baseT_Half
			| SUPPORTED_10baseT_Full
			| SUPPORTED_100baseT_Half
			| SUPPORTED_100baseT_Full
			| SUPPORTED_1000baseT_Half
			| SUPPORTED_1000baseT_Full
			| SUPPORTED_Autoneg| SUPPORTED_TP;

		if (hw->chip_id == CHIP_ID_GENESIS)
			supported &= ~(SUPPORTED_10baseT_Half
					     | SUPPORTED_10baseT_Full
					     | SUPPORTED_100baseT_Half
					     | SUPPORTED_100baseT_Full);

		else if (hw->chip_id == CHIP_ID_YUKON)
			supported &= ~SUPPORTED_1000baseT_Half;
	} else
		supported = SUPPORTED_1000baseT_Full | SUPPORTED_1000baseT_Half
			| SUPPORTED_FIBRE | SUPPORTED_Autoneg;

	return supported;
}
