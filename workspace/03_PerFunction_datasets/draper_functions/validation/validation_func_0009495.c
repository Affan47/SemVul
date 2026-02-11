gdome_xml_doc_getElementById (GdomeDocument *self, GdomeDOMString *elementId, GdomeException *exc) {
	Gdome_xml_Document *priv = (Gdome_xml_Document *)self;
	xmlHashTable *ids = NULL;
	idsIterator iter;

	g_return_val_if_fail (priv != NULL, NULL);
	g_return_val_if_fail (GDOME_XML_IS_DOC (priv), NULL);
	g_return_val_if_fail (elementId != NULL, NULL);
	g_return_val_if_fail (exc != NULL, NULL);

	ids = (xmlHashTable *)priv->n->ids;

	iter.elementId = (xmlChar *)elementId->str;
	iter.element = NULL;
	xmlHashScan(ids, idsHashScanner, &iter);

	return (GdomeElement *)gdome_xml_n_mkref (iter.element);
}
