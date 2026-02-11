nemo_property_page_dispose (GObject *object)
{
	NemoPropertyPage *page;

	page = NEMO_PROPERTY_PAGE (object);

	if (page->details->label) {
		g_object_unref (page->details->label);
		page->details->label = NULL;
	}
	if (page->details->page) {
		g_object_unref (page->details->page);
		page->details->page = NULL;
	}
}
