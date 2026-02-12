cmdline_toggle_langmap(long *b_im_ptr)
{
    if (map_to_exists_mode((char_u *)"", LANGMAP, FALSE))
    {

	State ^= LANGMAP;
#ifdef HAVE_INPUT_METHOD
	im_set_active(FALSE);
#endif
	if (b_im_ptr != NULL)
	{
	    if (State & LANGMAP)
		*b_im_ptr = B_IMODE_LMAP;
	    else
		*b_im_ptr = B_IMODE_NONE;
	}
    }
#ifdef HAVE_INPUT_METHOD
    else
    {


	if ((p_imdisable && b_im_ptr != NULL)
		? *b_im_ptr == B_IMODE_IM : im_get_status())
	{
	    im_set_active(FALSE);
	    if (b_im_ptr != NULL)
		*b_im_ptr = B_IMODE_NONE;
	}
	else
	{
	    im_set_active(TRUE);
	    if (b_im_ptr != NULL)
		*b_im_ptr = B_IMODE_IM;
	}
    }
#endif
    if (b_im_ptr != NULL)
    {
	if (b_im_ptr == &curbuf->b_p_iminsert)
	    set_iminsert_global();
	else
	    set_imsearch_global();
    }
#ifdef CURSOR_SHAPE
    ui_cursor_shape();
#endif
#if defined(FEAT_KEYMAP)

    status_redraw_curbuf();
#endif
}
