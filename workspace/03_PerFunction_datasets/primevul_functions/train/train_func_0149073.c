xmlReconciliateNs(xmlDocPtr doc, xmlNodePtr tree) {
    xmlNsPtr *oldNs = NULL;
    xmlNsPtr *newNs = NULL;
    int sizeCache = 0;
    int nbCache = 0;

    xmlNsPtr n;
    xmlNodePtr node = tree;
    xmlAttrPtr attr;
    int ret = 0, i;

    if ((node == NULL) || (node->type != XML_ELEMENT_NODE)) return(-1);
    if ((doc == NULL) || (doc->type != XML_DOCUMENT_NODE)) return(-1);
    if (node->doc != doc) return(-1);
    while (node != NULL) {


	if (node->ns != NULL) {


	    if (sizeCache == 0) {
		sizeCache = 10;
		oldNs = (xmlNsPtr *) xmlMalloc(sizeCache *
					       sizeof(xmlNsPtr));
		if (oldNs == NULL) {
		    xmlTreeErrMemory("fixing namespaces");
		    return(-1);
		}
		newNs = (xmlNsPtr *) xmlMalloc(sizeCache *
					       sizeof(xmlNsPtr));
		if (newNs == NULL) {
		    xmlTreeErrMemory("fixing namespaces");
		    xmlFree(oldNs);
		    return(-1);
		}
	    }
	    for (i = 0;i < nbCache;i++) {
	        if (oldNs[i] == node->ns) {
		    node->ns = newNs[i];
		    break;
		}
	    }
	    if (i == nbCache) {


		n = xmlNewReconciliedNs(doc, tree, node->ns);
		if (n != NULL) {


		    if (sizeCache <= nbCache) {
		        sizeCache *= 2;
			oldNs = (xmlNsPtr *) xmlRealloc(oldNs, sizeCache *
			                               sizeof(xmlNsPtr));
		        if (oldNs == NULL) {
			    xmlTreeErrMemory("fixing namespaces");
			    xmlFree(newNs);
			    return(-1);
			}
			newNs = (xmlNsPtr *) xmlRealloc(newNs, sizeCache *
			                               sizeof(xmlNsPtr));
		        if (newNs == NULL) {
			    xmlTreeErrMemory("fixing namespaces");
			    xmlFree(oldNs);
			    return(-1);
			}
		    }
		    newNs[nbCache] = n;
		    oldNs[nbCache++] = node->ns;
		    node->ns = n;
                }
	    }
	}


	if (node->type == XML_ELEMENT_NODE) {
	    attr = node->properties;
	    while (attr != NULL) {
		if (attr->ns != NULL) {


		    if (sizeCache == 0) {
			sizeCache = 10;
			oldNs = (xmlNsPtr *) xmlMalloc(sizeCache *
						       sizeof(xmlNsPtr));
			if (oldNs == NULL) {
			    xmlTreeErrMemory("fixing namespaces");
			    return(-1);
			}
			newNs = (xmlNsPtr *) xmlMalloc(sizeCache *
						       sizeof(xmlNsPtr));
			if (newNs == NULL) {
			    xmlTreeErrMemory("fixing namespaces");
			    xmlFree(oldNs);
			    return(-1);
			}
		    }
		    for (i = 0;i < nbCache;i++) {
			if (oldNs[i] == attr->ns) {
			    attr->ns = newNs[i];
			    break;
			}
		    }
		    if (i == nbCache) {


			n = xmlNewReconciliedNs(doc, tree, attr->ns);
			if (n != NULL) {


			    if (sizeCache <= nbCache) {
				sizeCache *= 2;
				oldNs = (xmlNsPtr *) xmlRealloc(oldNs,
				           sizeCache * sizeof(xmlNsPtr));
				if (oldNs == NULL) {
				    xmlTreeErrMemory("fixing namespaces");
				    xmlFree(newNs);
				    return(-1);
				}
				newNs = (xmlNsPtr *) xmlRealloc(newNs,
				           sizeCache * sizeof(xmlNsPtr));
				if (newNs == NULL) {
				    xmlTreeErrMemory("fixing namespaces");
				    xmlFree(oldNs);
				    return(-1);
				}
			    }
			    newNs[nbCache] = n;
			    oldNs[nbCache++] = attr->ns;
			    attr->ns = n;
			}
		    }
		}
		attr = attr->next;
	    }
	}


        if ((node->children != NULL) && (node->type != XML_ENTITY_REF_NODE)) {

	    node = node->children;
	} else if ((node != tree) && (node->next != NULL)) {

	    node = node->next;
	} else if (node != tree) {

	    while (node != tree) {
	        if (node->parent != NULL)
		    node = node->parent;
		if ((node != tree) && (node->next != NULL)) {
		    node = node->next;
		    break;
		}
		if (node->parent == NULL) {
		    node = NULL;
		    break;
		}
	    }

	    if (node == tree)
	        node = NULL;
	} else
	    break;
    }
    if (oldNs != NULL)
	xmlFree(oldNs);
    if (newNs != NULL)
	xmlFree(newNs);
    return(ret);
}
