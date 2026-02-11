place_labels3d(struct text_label *listhead, int layer)
{
    struct text_label *this_label;
    int x, y;

    if (term->pointsize)
	(*term->pointsize)(pointsize);

    for (this_label = listhead;
	 this_label != NULL;
	 this_label = this_label->next) {

	if (this_label->layer != layer)
	    continue;


	if (layer == LAYER_PLOTLABELS) {
	    double xx, yy;
	    map3d_xy_double(this_label->place.x, this_label->place.y,
		     this_label->place.z, &xx, &yy);
	    x = xx;
	    y = yy;

	    if (splot_map && clip_point(x, y))
		continue;
	} else
	    map3d_position(&this_label->place, &x, &y, "label");

	write_label(x, y, this_label);
    }
}
