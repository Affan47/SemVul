parse_shape(Window win, colorset_t *cs, int i, char *args,
			int *has_shape_changed)
{
	char *token;
	static char *name = "parse_colorset(shape)";
	FvwmPicture *picture;
	FvwmPictureAttributes fpa;

	if (!FHaveShapeExtension)
	{
		cs->shape_mask = None;
		return;
	}


	token = PeekToken(args, &args);
	*has_shape_changed = True;
	if (cs->shape_mask)
	{
		add_to_junk(cs->shape_mask);
		cs->shape_mask = None;
	}


	if (csetopts[i][0] == 'T')
	{
		cs->shape_type = SHAPE_TILED;
	}
	else if (csetopts[i][0] == 'A')
	{
		cs->shape_type = SHAPE_STRETCH_ASPECT;
	}
	else
	{
		cs->shape_type = SHAPE_STRETCH;
	}
	fpa.mask = FPAM_NO_ALPHA;


	if (!token)
	{
		return;
	}


	picture = PCacheFvwmPicture(dpy, win, NULL, token, fpa);
	if (!picture)
	{
		fvwm_msg(ERR, name, "can't load picture %s", token);
	}
	else if (picture->depth != 1 && picture->mask == None)
	{
		fvwm_msg(ERR, name, "shape pixmap must be of depth 1");
		SafeDestroyPicture(dpy, picture);
	}
	else
	{
		Pixmap mask;


		if (picture->mask != None)
		{
			mask = picture->mask;
		}
		else
		{
			mask = picture->picture;
		}
		cs->shape_width = picture->width;
		cs->shape_height = picture->height;

		if (mask != None)
		{
			cs->shape_mask = XCreatePixmap(
				dpy, mask, picture->width, picture->height, 1);
			if (cs->shape_mask != None)
			{
				XCopyPlane(dpy, mask, cs->shape_mask,
					   Scr.MonoGC, 0, 0, picture->width,
					   picture->height, 0, 0, 1);
			}
		}
	}
	if (picture)
	{
		SafeDestroyPicture(dpy, picture);
		picture = None;
	}
	return;
}
