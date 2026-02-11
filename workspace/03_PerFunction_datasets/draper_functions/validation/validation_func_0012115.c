setScrollX(int vl)
{
	GtkAdjustment* adj;
	int max;

	if (!_scroll)
		return;

	adj = gtk_scrolled_window_get_hadjustment(_scroll);

	max = (int)(adj->upper - adj->page_size);

	if (vl < 0)
		vl = 0;
	else if (vl > max)
		vl = max;

	gtk_adjustment_set_value(adj, (gdouble)vl);
}
