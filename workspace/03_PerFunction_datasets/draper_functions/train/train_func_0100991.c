sys_retrieve_identity (xmlNodePtr node, int *err)
{
    identity *ident;
    xmlNodePtr cur;
    int n_atoms, depvar;
    int i, got = 0;

    got += gretl_xml_get_prop_as_int(node, "n_atoms", &n_atoms);
    got += gretl_xml_get_prop_as_int(node, "depvar", &depvar);
    if (got < 2) {
	*err = E_DATA;
	return NULL;
    }

    ident = ident_new(n_atoms);
    if (ident == NULL) {
	*err = E_ALLOC;
	return NULL;
    }

    ident->depvar = depvar;

    cur = node->xmlChildrenNode;

    i = 0;
    while (cur != NULL && !*err) {
	if (!xmlStrcmp(cur->name, (XUC) "id_atom")) {
	    got = gretl_xml_get_prop_as_int(cur, "op", &ident->atoms[i].op);
	    got += gretl_xml_get_prop_as_int(cur, "varnum", &ident->atoms[i].varnum);
	    if (got < 2) {
		*err = E_DATA;
	    } else {
		i++;
	    }
	}
	cur = cur->next;
    }

    if (!*err && i != n_atoms) {
	*err = E_DATA;
    }

    if (*err) {
	destroy_ident(ident);
	ident = NULL;
    }

    return ident;
}
