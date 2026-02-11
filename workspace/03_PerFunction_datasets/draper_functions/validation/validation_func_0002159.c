gdome_xml_el_attributes (GdomeNode *self, GdomeException *exc)
{
	Gdome_xml_Node *priv = (Gdome_xml_Node *)self;

  g_return_val_if_fail (priv != NULL, NULL);
	g_return_val_if_fail (GDOME_XML_IS_EL (priv), NULL);
  g_return_val_if_fail (exc != NULL, NULL);

  return gdome_xml_nnm_mkref(gdome_xml_doc_mkref (gdome_xmlGetOwner (priv->n)),
                             (GdomeElement *)self, gdome_xmlGetAttrList(priv->n), gdome_xmlGetNsDeclList(priv->n),
                             priv->accessType, GDOME_ATTRIBUTE_NODE);
}
