ParseNodes (xmlNodePtr node)
{
	Residue* r;
	while (node) {
		if (!strcmp ((char*) node->name, "residue")) {
			r = new Residue ();
			r->Load (node, this);
		}
		node = node->next;
	}
}
