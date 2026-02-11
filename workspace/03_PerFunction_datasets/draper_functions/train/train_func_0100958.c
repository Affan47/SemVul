tech_common_render()
{
	char buf[256];
	int y, z, font_height;


	gr_set_color_fast(&Color_text_normal);
	techroom_render_desc(Tech_desc_coords[gr_screen.res][SHIP_X_COORD], Tech_desc_coords[gr_screen.res][SHIP_Y_COORD], Tech_desc_coords[gr_screen.res][SHIP_H_COORD]);

	font_height = gr_get_font_height();


	y = 0;
	z = List_offset;
	while (y + font_height <= Tech_list_coords[gr_screen.res][SHIP_H_COORD]) {
		if (z >= Current_list_size) {
			break;
		}

		if (z == Cur_entry) {
			gr_set_color_fast(&Color_text_selected);
		} else if (z == Select_tease_line) {
			gr_set_color_fast(&Color_text_subselected);
		} else {
			gr_set_color_fast(&Color_text_normal);
		}

		memset( buf, 0, sizeof(buf) );
		strncpy(buf, Current_list[z].name, sizeof(buf) - 1);

		if (Lcl_gr)
			lcl_translate_ship_name(buf);

		gr_force_fit_string(buf, 255, Tech_list_coords[gr_screen.res][SHIP_W_COORD]);
		gr_string(Tech_list_coords[gr_screen.res][SHIP_X_COORD], Tech_list_coords[gr_screen.res][SHIP_Y_COORD] + y, buf);

		List_buttons[z - List_offset].update_dimensions(Tech_list_coords[gr_screen.res][SHIP_X_COORD], Tech_list_coords[gr_screen.res][SHIP_Y_COORD] + y, Tech_list_coords[gr_screen.res][SHIP_W_COORD], font_height);
		List_buttons[z - List_offset].enable(1);

		y += font_height;
		z++;
	}


	z -= List_offset;
	while (z < LIST_BUTTONS_MAX) {
		List_buttons[z++].disable();
	}
}
