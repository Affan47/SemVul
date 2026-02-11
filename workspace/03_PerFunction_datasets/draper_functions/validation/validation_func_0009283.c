simplify(Solver& s, bool sh) {
	ClauseDB::size_type i, j, end = integrated_.size();
	for (i = j = 0; i != end; ++i) {
		Constraint* c = integrated_[i];
		if (c->simplify(s, sh)) {
			c->destroy(&s, false);
			intTail_ -= (i < intTail_);
		}
		else                    {
			integrated_[j++] = c;
		}
	}
	shrinkVecTo(integrated_, j);
	if (intTail_ > integrated_.size()) intTail_ = integrated_.size();
	return false;
}
