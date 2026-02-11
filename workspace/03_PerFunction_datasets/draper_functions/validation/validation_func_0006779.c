ir_edit_reconfigure(GxIREdit *ir_edit)
{
	if (!ir_edit->width) {
		return;
	}
	gboolean home_pos = (FP_EQUAL(ir_edit->scale, ir_edit_get_default_scale(ir_edit)) &&
	                     ir_edit->current_offset == min(0, int(floor(-ir_edit->offset/ir_edit->scale))));
	ir_edit->x_off = (int)(ir_edit->text_width+ir_edit->label_sep+ir_edit->x_border);
	ir_edit->y_off = ir_edit->text_height+ir_edit->y_border_top;
	ir_edit->graph_x = ir_edit->width-ir_edit->x_off-ir_edit->x_border;
	ir_edit->graph_y = ir_edit->height-ir_edit->y_off-ir_edit->y_border_bottom;
	ir_edit->scale_height = -ir_edit->graph_y/(ir_edit->max_y-ir_edit->min_y);
	if (ir_edit->data) {
		if (!ir_edit->scale) {
			gx_ir_edit_home(ir_edit);
		} else {
			next_regular_tick(ir_edit, ir_edit->label_width*ir_edit->scale/ir_edit->fs);
			ir_edit_precalc(ir_edit);
			if (home_pos) {
				gx_ir_edit_home(ir_edit);
			}
		}
	}
}
