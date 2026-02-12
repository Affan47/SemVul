XMLNode::child (const char* name) const
{


	XMLNodeConstIterator cur;

	if (name == 0) {
		return 0;
	}

	for (cur = _children.begin(); cur != _children.end(); ++cur) {
		if ((*cur)->name() == name) {
			return *cur;
		}
	}

	return 0;
}
