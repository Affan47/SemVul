setpalette(const char *pal_name)
{
	ht_view *v=first;
	while (v) {
		if (strcmp(pal_class, v->pal_class)==0) v->setpalette(pal_name);
		v=v->next;
	}
	ht_view::setpalette(pal_name);
}
