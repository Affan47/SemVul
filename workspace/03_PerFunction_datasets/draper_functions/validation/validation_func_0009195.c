sync_width(TextFieldWidget w, long old_w, long new_w)
{
    long	max, width = w->scrollable.width;

    old_w++;
    new_w++;
    if (new_w < width && old_w < width)
	return;

    max = 1;
    if (old_w < width || new_w <= old_w)
	max = max_width(w) + 1;
    if (max < new_w)
	max = new_w;

    if (max == width)
	return;

    w->scrollable.width = max;
    ScrollableFitHBar((ScrollableWidget)w);
}
