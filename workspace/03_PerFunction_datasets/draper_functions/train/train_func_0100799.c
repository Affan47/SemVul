write_switches(struct fpga_bits* bits, struct fpga_model* model)
{
	struct fpga_tile* tile;
	int x, y, i;

	RC_CHECK(model);


	for (x = 0; x < model->x_width; x++) {
		for (y = 0; y < model->y_height; y++) {
			tile = YX_TILE(model, y, x);
			if (is_atx(X_ROUTING_COL, model, x)
			    && y >= TOP_IO_TILES
			    && y < model->y_height-BOT_IO_TILES
			    && !is_aty(Y_ROW_HORIZ_AXSYMM|Y_CHIP_HORIZ_REGS,
					model, y)) {
				write_routing_sw(bits, model, y, x);
				continue;
			}
			if (is_atyx(YX_DEV_ILOGIC, model, y, x)) {
				write_iologic_sw(bits, model, y, x);
				continue;
			}
			if (is_atyx(YX_DEV_LOGIC, model, y, x)) {
				write_logic_sw(bits, model, y, x);
				continue;
			}
			if (is_atyx(YX_DEV_IOB, model, y, x))
				continue;
			if (is_atx(X_ROUTING_COL, model, x)
			    && is_aty(Y_ROW_HORIZ_AXSYMM, model, y)) {
				write_hclk_sw(bits, model, y, x);
				continue;
			}
			if (is_atyx(YX_INNER_TERM, model, y, x)) {
				write_inner_term_sw(bits, model, y, x);
				continue;
			}
			if (is_atyx(YX_CENTER, model, y, x)) {
				write_center_sw(bits, model, y, x);
				continue;
			}
			if (is_atx(X_CENTER_REGS_COL, model, x)) {
				if (is_aty(Y_ROW_HORIZ_AXSYMM, model, y)) {
					write_gclk_center_vert_sw(bits, model, y, x);
					continue;
				}
				if (tile->flags & TF_CENTER_MIDBUF
				    || (y < model->center_y
				     && YX_TILE(model, y+1, x)->flags & TF_CENTER_MIDBUF)
				    || (y > model->center_y
				        && YX_TILE(model, y-1, x)->flags & TF_CENTER_MIDBUF))
					continue;
			}

			for (i = 0; i < tile->num_switches; i++) {
				if (!(tile->switches[i] & SWITCH_USED))
					continue;
				fprintf(stderr, "#E %s:%i unsupported switch "
					"y%i x%i %s\n", __FILE__, __LINE__,
					y, x,
					fpga_switch_print(model, y, x, i));
			}
		}
	}
	RC_RETURN(model);
}
