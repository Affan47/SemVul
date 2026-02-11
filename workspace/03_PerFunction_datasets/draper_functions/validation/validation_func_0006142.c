maximize()
{
	if(trans) return;

	if(is_shaded)
	{
		shade();
		return;
	}

	if(! is_maximized)
	{
		old_x=x;
		old_y=y;
		old_width=width;
		old_height=height;


		if (size->flags & PMaxSize) {

			width = size->max_width;
	        	height = size->max_height;

			XMoveResizeWindow(dpy, frame, x, y-theight(), width, height+theight());

	    	} else {

			x=0;
			y=0;
			width=xres;
			height=yres;

			XMoveResizeWindow(dpy, frame, x, y, width, height);

			y = theight();
			height -= theight();
		}

		is_maximized=true;
	} else {

		x=old_x;
		y=old_y;
		width=old_width;
		height=old_height;

		XMoveResizeWindow(dpy, frame,
        		old_x, old_y - theight(), old_width, old_height + theight());

		is_maximized=false;

		if(is_shaded) is_shaded=false;
	}

	XResizeWindow(dpy, title, width, theight());
	XResizeWindow(dpy, window, width, height);

	sendConfig();
}
