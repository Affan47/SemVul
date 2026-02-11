check_diport_of_integrated_lvds(
	struct lvds_chip_information *plvds_chip_info,
				     struct lvds_setting_information
				     *plvds_setting_info)
{

	switch (viafb_display_hardware_layout) {
	case HW_LAYOUT_LCD_ONLY:
		{
			if (plvds_setting_info->device_lcd_dualedge) {
				plvds_chip_info->output_interface =
				    INTERFACE_LVDS0LVDS1;
			} else {
				plvds_chip_info->output_interface =
				    INTERFACE_LVDS0;
			}

			break;
		}

	case HW_LAYOUT_DVI_ONLY:
		{
			plvds_chip_info->output_interface = INTERFACE_NONE;
			break;
		}

	case HW_LAYOUT_LCD1_LCD2:
	case HW_LAYOUT_LCD_EXTERNAL_LCD2:
		{
			plvds_chip_info->output_interface =
			    INTERFACE_LVDS0LVDS1;
			break;
		}

	case HW_LAYOUT_LCD_DVI:
		{
			plvds_chip_info->output_interface = INTERFACE_LVDS1;
			break;
		}

	default:
		{
			plvds_chip_info->output_interface = INTERFACE_LVDS1;
			break;
		}
	}

	DEBUG_MSG(KERN_INFO
		  "Display Hardware Layout: 0x%x, LCD DI Port: 0x%x\n",
		  viafb_display_hardware_layout,
		  plvds_chip_info->output_interface);
}
