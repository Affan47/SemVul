AAllocColor(AWindow *a, Display *display, Colormap colormap, XColor *c)
{
	Status result;
	result = XAllocColor (display, colormap, c);
	if (result) {
#ifdef X11
		a->color_to_pixel_map[a->color_to_pixel_map_top] = c->pixel;
		c->pixel = a->color_to_pixel_map_top;
		a->color_to_pixel_map_top++;
#endif
	}
	return result;
}
