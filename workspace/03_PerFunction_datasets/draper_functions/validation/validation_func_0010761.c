foreach_save_func (gpointer key,
                   gpointer value,
                   gpointer user_data)
{
	struct save_data *sd = user_data;
	xmlNodePtr new_node;
	xmlChar *enc;

	if (sd->type == E_XML_HASH_TYPE_OBJECT_UID) {
		new_node = xmlNewNode (NULL, (xmlChar *)"object");
		xmlNewProp (new_node, (xmlChar *)"uid", (const xmlChar *) key);
	} else
		new_node = xmlNewNode (NULL, (const xmlChar *) key);

	enc = xmlEncodeEntitiesReentrant (sd->doc, value);
	xmlNodeSetContent (new_node, enc);
	xmlFree (enc);

	xmlAddChild (sd->root, new_node);
}
