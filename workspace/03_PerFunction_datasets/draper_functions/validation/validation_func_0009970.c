flickr_photo_create_element (DomDomizable *base,
			     DomDocument  *doc)
{
	FlickrPhoto *self;
	DomElement  *element;

	self = FLICKR_PHOTO (base);

	element = dom_document_create_element (doc, "photo", NULL);
	if (self->id != NULL)
		dom_element_set_attribute (element, "id", self->id);
	if (self->secret != NULL)
		dom_element_set_attribute (element, "secret", self->secret);
	if (self->server != NULL)
		dom_element_set_attribute (element, "server", self->server);
	if (self->title != NULL)
		dom_element_set_attribute (element, "title", self->title);
	if (self->is_primary)
		dom_element_set_attribute (element, "isprimary", "1");

	return element;
}
