_gfxwop_pic_view_draw(gfxw_widget_t *widget, point_t pos)
{
	gfxw_dyn_view_t *view = (gfxw_dyn_view_t *) widget;
	DRAW_ASSERT(widget, GFXW_PIC_VIEW);

	GFX_ASSERT(gfxop_set_clip_zone(view->visual->gfx_state, view->parent->zone));
	GFX_ASSERT(gfxop_draw_cel_static_clipped(view->visual->gfx_state,
						 view->view, view->loop,
						 view->cel,
						 _move_point(view->draw_bounds, pos),
						 view->color, view->palette));


	GFX_ASSERT(gfxop_draw_cel(view->visual->gfx_state,
				  view->view, view->loop,
				  view->cel,
				  _move_point(view->draw_bounds, pos),
				  view->color, view->palette));


	widget->draw = _gfxwop_draw_nop;


	return 0;
}
