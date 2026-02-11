PGraphicsCreateStretchPicture(
	Display *dpy, Window win, FvwmPicture *src,
	int dest_width, int dest_height, GC gc, GC mono_gc, GC alpha_gc)
{
	Pixmap pixmap = None, mask = None, alpha = None;
	FvwmPicture *q;

	if (src == NULL || src->picture == None)
	{
		return NULL;
	}
	pixmap = CreateStretchPixmap(
		dpy, src->picture, src->width, src->height, src->depth,
		dest_width, dest_height, gc);
	if (!pixmap)
	{
		return NULL;
	}
	if (src->mask)
	{
		mask = CreateStretchPixmap(
			dpy, src->mask, src->width, src->height, 1,
			dest_width, dest_height, mono_gc);
	}
	if (src->alpha)
	{
		alpha = CreateStretchPixmap(
			dpy, src->alpha, src->width, src->height,
			FRenderGetAlphaDepth(),
			dest_width, dest_height, alpha_gc);
	}

	q = (FvwmPicture*)safemalloc(sizeof(FvwmPicture));
	memset(q, 0, sizeof(FvwmPicture));
	q->count = 1;
	q->name = NULL;
	q->next = NULL;
	q->stamp = pixmap;
	q->picture = pixmap;
	q->mask = mask;
	q->alpha = alpha;
	q->width = dest_width;
	q->height = dest_height;
	q->depth = src->depth;
	q->alloc_pixels = 0;
	q->nalloc_pixels = 0;

	return q;
}
