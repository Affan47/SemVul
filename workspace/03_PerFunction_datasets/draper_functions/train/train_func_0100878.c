maybeFlashDock(int flash_fast)
{
	int draw_bright=0;

	setGaugeColor();
	if ( !timestamp_elapsed(flash_timer[0]) ) {
		if ( timestamp_elapsed(flash_timer[1]) ) {
			if ( flash_fast ) {
				flash_timer[1] = timestamp(fl2i(TBOX_FLASH_INTERVAL/2.0f));
			} else {
				flash_timer[1] = timestamp(TBOX_FLASH_INTERVAL);
			}


			if(flash_flags)
				flash_flags = false;
			else
				flash_flags = true;
		}

		if (flash_flags) {
			setGaugeColor(HUD_C_BRIGHT);
			draw_bright=1;
		} else {
			setGaugeColor(HUD_C_DIM);
		}
	}

	return draw_bright;
}
