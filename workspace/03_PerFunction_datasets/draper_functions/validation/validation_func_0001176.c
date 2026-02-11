gfxop_get_cel_parameters(gfx_state_t *state, int nr, int loop, int cel,
			 int *width, int *height, point_t *offset)
{
	gfxr_view_t *view = NULL;
	gfx_pixmap_t *pxm = NULL;
	BASIC_CHECKS(GFX_ERROR);

	if (!(view = gfxr_get_view(state->resstate, nr, &loop, &cel, 0))) {
		GFXWARN("Attempt to get cel parameters for invalid view %d\n", nr);
		return GFX_ERROR;
	}

	pxm = view->loops[loop].cels[cel];
	*width = pxm->index_xl;
	*height = pxm->index_yl;
	offset->x = pxm->xoffset;
	offset->y = pxm->yoffset;

	return GFX_OK;
}
