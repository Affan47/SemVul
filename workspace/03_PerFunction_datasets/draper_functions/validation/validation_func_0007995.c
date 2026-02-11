viafb_lcd_disable(void)
{

	if (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CLE266) {
		lcd_powersequence_off();

		viafb_write_reg_mask(SR1E, VIASR, 0x00, 0x30);
	} else if (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CX700) {
		if (viafb_LCD2_ON
		    && (INTEGRATED_LVDS ==
			viaparinfo->chip_info->lvds_chip_info2.lvds_chip_name))
			integrated_lvds_disable(viaparinfo->lvds_setting_info,
				&viaparinfo->chip_info->lvds_chip_info2);
		if (INTEGRATED_LVDS ==
			viaparinfo->chip_info->lvds_chip_info.lvds_chip_name)
			integrated_lvds_disable(viaparinfo->lvds_setting_info,
				&viaparinfo->chip_info->lvds_chip_info);
		if (VT1636_LVDS == viaparinfo->chip_info->
			lvds_chip_info.lvds_chip_name)
			viafb_disable_lvds_vt1636(viaparinfo->lvds_setting_info,
				&viaparinfo->chip_info->lvds_chip_info);
	} else if (VT1636_LVDS ==
	viaparinfo->chip_info->lvds_chip_info.lvds_chip_name) {
		viafb_disable_lvds_vt1636(viaparinfo->lvds_setting_info,
				    &viaparinfo->chip_info->lvds_chip_info);
	} else {

		viafb_write_reg_mask(SR3D, VIASR, 0x00, 0x20);

		viafb_write_reg_mask(CR91, VIACR, 0x80, 0x80);
	}


	viafb_write_reg_mask(CR79, VIACR, 0x00, 0x01);

	viafb_write_reg_mask(CR6B, VIACR, 0x00, 0x08);
}
