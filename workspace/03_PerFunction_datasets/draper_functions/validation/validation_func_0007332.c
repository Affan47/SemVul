if1_reset( int hard_reset GCC_UNUSED )
{
  if1_active = 0;
  if1_available = 0;

  if( !periph_is_active( PERIPH_TYPE_INTERFACE1 ) ) {
    ui_statusbar_update( UI_STATUSBAR_ITEM_MICRODRIVE,
                         UI_STATUSBAR_STATE_NOT_AVAILABLE );

    return;
  }


  if( machine_load_rom_bank( if1_memory_map_romcs, 0,
			     settings_current.rom_interface_i,
			     settings_default.rom_interface_i,
			     0x2000 ) ) {
    settings_current.interface1 = 0;
    periph_activate_type( PERIPH_TYPE_INTERFACE1, 0 );

    ui_statusbar_update( UI_STATUSBAR_ITEM_MICRODRIVE,
                         UI_STATUSBAR_STATE_NOT_AVAILABLE );

    return;
  }

  machine_current->ram.romcs = 0;

  if1_ula.cts = 2;
  if1_ula.comms_clk = 0;
  if1_ula.comms_data = 0;
  if1_ula.net = 0;
  if1_ula.esc_in = 0;

  microdrives_reset();

  update_menu( UMENU_ALL );
  ui_statusbar_update( UI_STATUSBAR_ITEM_MICRODRIVE,
		       UI_STATUSBAR_STATE_INACTIVE );

  if1_mdr_status = 0;

  if1_available = 1;
}
