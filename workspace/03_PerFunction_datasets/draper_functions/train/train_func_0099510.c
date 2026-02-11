lvds_identify_integratedlvds(void)
{
	if (viafb_display_hardware_layout == HW_LAYOUT_LCD_EXTERNAL_LCD2) {


		if (viaparinfo->chip_info->lvds_chip_info.lvds_chip_name) {
			viaparinfo->chip_info->lvds_chip_info2.lvds_chip_name =
			    INTEGRATED_LVDS;
			DEBUG_MSG(KERN_INFO "Support two dual channel LVDS! "
				  "(Internal LVDS + External LVDS)\n");
		} else {
			viaparinfo->chip_info->lvds_chip_info.lvds_chip_name =
			    INTEGRATED_LVDS;
			DEBUG_MSG(KERN_INFO "Not found external LVDS, "
				  "so can't support two dual channel LVDS!\n");
		}
	} else if (viafb_display_hardware_layout == HW_LAYOUT_LCD1_LCD2) {

		viaparinfo->chip_info->lvds_chip_info.lvds_chip_name =
		INTEGRATED_LVDS;
		viaparinfo->chip_info->lvds_chip_info2.lvds_chip_name =
			INTEGRATED_LVDS;
		DEBUG_MSG(KERN_INFO "Support two single channel LVDS! "
			  "(Internal LVDS + Internal LVDS)\n");
	} else if (viafb_display_hardware_layout != HW_LAYOUT_DVI_ONLY) {


		if (!viaparinfo->chip_info->lvds_chip_info.lvds_chip_name) {
			viaparinfo->chip_info->lvds_chip_info.lvds_chip_name =
			    INTEGRATED_LVDS;
			DEBUG_MSG(KERN_INFO "Found Integrated LVDS!\n");
		}
	} else {
		viaparinfo->chip_info->lvds_chip_info.lvds_chip_name =
			NON_LVDS_TRANSMITTER;
		DEBUG_MSG(KERN_INFO "Do not support LVDS!\n");
		return false;
	}

	return true;
}
