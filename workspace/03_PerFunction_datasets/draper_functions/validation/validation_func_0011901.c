is_compat(match *m1, match *m2) {
	if(m2->has_failed) return false;

	map<name,name> m1n = m1->get_names();
	map<name,name> m2n = m2->get_names();

	for(map<name,name>::iterator i = m1n.begin(); i != m1n.end(); i++) {
		if(m2n.find(i->first) == m2n.end()) continue;

		if(m2n[i->first] != i->second) return false;
	}

	map<term*,term*> mapping = m1->get_mappings();

	for(map<term*,term*>::iterator i = mapping.begin(); i!=mapping.end(); i++) {
		if(m2->get_mapping(i->first) == NULL) continue;

		if(m2->get_mapping(i->first) != i->second) return false;
	}

	return true;
}
