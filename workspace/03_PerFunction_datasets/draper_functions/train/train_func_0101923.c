ir_edit_gainline(GxIREdit *ir_edit, cairo_t *c, GdkEventExpose *event)
{
	GxRgba clr;
	get_color(ir_edit, &clr, "gain-line-color", &gain_line_color);
	double j, g;
	int n;
	gain_points *p;
	if (ir_edit->linear || !ir_edit->data) {
		return;
	}
	cairo_save(c);
	cairo_rectangle(c,0, 0, ir_edit->graph_x, ir_edit->graph_y);
	cairo_clip(c);
	cairo_set_line_width(c,1.0);
	cairo_set_source_rgba(c, clr.red, clr.green, clr.blue, clr.alpha);
	gboolean first = TRUE;
	for (p = ir_edit->gains, n = 0; n < ir_edit->gains_len; n++, p++) {
		j = int(p->i / ir_edit->scale) - ir_edit->current_offset;
		g = (p->g - ir_edit->max_y) * ir_edit->scale_height;
		if (first) {
			first = FALSE;
			cairo_move_to(c,j, g);
		} else {
			cairo_line_to(c,j, g);
		}
	}
	cairo_stroke(c);
	for (p = ir_edit->gains, n = 0; n < ir_edit->gains_len; n++, p++) {
		j = int(p->i / ir_edit->scale) - ir_edit->current_offset + 0.5;
		g = (p->g - ir_edit->max_y) * ir_edit->scale_height + 0.5;
		cairo_arc(c,j, g, ir_edit->dot_diameter, 0.0, 2.0*M_PI);
		cairo_fill(c);
	}
	cairo_restore(c);
}
