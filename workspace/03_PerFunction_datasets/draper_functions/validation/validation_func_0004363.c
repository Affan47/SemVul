gfxw_new_text(gfx_state_t *state, rect_t area, int font, const char *text, gfx_alignment_t halign,
	      gfx_alignment_t valign, gfx_color_t color1, gfx_color_t color2,
	      gfx_color_t bgcolor, int text_flags)
{
	gfxw_text_t *widget = (gfxw_text_t *)
		_gfxw_new_widget(sizeof(gfxw_text_t), GFXW_TEXT);

	widget->widget_priority = _gfxw_color_get_priority(color1);
	widget->font_nr = font;
	widget->text = (char*)sci_malloc(strlen(text) + 1);
	widget->halign = halign;
	widget->valign = valign;
	widget->color1 = color1;
	widget->color2 = color2;
	widget->bgcolor = bgcolor;
	widget->text_flags = text_flags;
	widget->text_handle = NULL;

	strcpy(widget->text, text);

	gfxop_get_text_params(state, font, text, area.xl, &(widget->width),
			      &(widget->height), text_flags,
			      &(widget->lines_nr), &(widget->lineheight),
			      &(widget->lastline_width));


	if (halign == ALIGN_LEFT)
		area.xl = widget->width;
	if (valign == ALIGN_TOP)
		area.yl = widget->height;

	widget->bounds = area;

	widget->flags |= GFXW_FLAG_VISIBLE;

	_gfxw_set_ops_TEXT(GFXW(widget));

	return widget;
}
