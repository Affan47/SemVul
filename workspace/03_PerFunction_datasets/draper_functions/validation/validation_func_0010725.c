dom_get_nsdecl(xmlNode *node, xmlChar *localName) {
	xmlNsPtr cur;
	xmlNs *ret = NULL;
	if (node == NULL)
		return NULL;

	if (localName == NULL || xmlStrEqual(localName, (xmlChar *)"")) {
		cur = node->nsDef;
		while (cur != NULL) {
			if (cur->prefix == NULL  && cur->href != NULL) {
				ret = cur;
				break;
			}
			cur = cur->next;
		}
	} else {
		cur = node->nsDef;
		while (cur != NULL) {
			if (cur->prefix != NULL && xmlStrEqual(localName, cur->prefix)) {
				ret = cur;
				break;
			}
			cur = cur->next;
		}
	}
	return ret;
}
