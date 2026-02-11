g2_X11_query_pointer(int pid, void *pdp,
			 int *x, int *y, unsigned int *button)
{
    Bool rv;
    g2_X11_device *xout=&g2_X11_dev[pid];
    Window root, child;
    int rx, ry;

    rv = XQueryPointer(xout->display, xout->window,
		       &root, &child, &rx, &ry,
		       x, y, button);

    if(rv)
	return 0;
    else
	return 1;
}
