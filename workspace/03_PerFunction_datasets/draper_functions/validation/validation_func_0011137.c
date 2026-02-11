FTipsCheck(Display *dpy)
{
	unsigned long ct;

	if (state != FVWM_TIPS_WAITING || win == None)
	{
		return 0;
	}

	ct = __get_time();

	if (ct >= timeOut)
	{
		__map_window(dpy);
		XFlush(dpy);
		state = FVWM_TIPS_MAPPED;
		return 0;
	}
	else
	{
		XFlush(dpy);
		return timeOut - ct;
	}
}
