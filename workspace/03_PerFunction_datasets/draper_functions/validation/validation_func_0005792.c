unitPropagate() {
	assert(!hasConflict());
	Literal p, q, r;
	uint32 idx, ignore, DL = decisionLevel();
	const ShortImplicationsGraph& btig = shared_->shortImplications();
	while ( !assign_.qEmpty() ) {
		p             = assign_.qPop();
		idx           = p.index();
		WatchList& wl = watches_[idx];

		if (!btig.propagate(*this, p)) {
			return false;
		}

		if (wl.left_size() != 0) {
			WatchList::left_iterator it, end, j = wl.left_begin();
			Constraint::PropResult res;
			for (it = wl.left_begin(), end = wl.left_end();  it != end;  ) {
				ClauseWatch& w = *it++;
				res = w.head->ClauseHead::propagate(*this, p, ignore);
				if (res.keepWatch) {
					*j++ = w;
				}
				if (!res.ok) {
					wl.shrink_left(std::copy(it, end, j));
					return false;
				}
			}
			wl.shrink_left(j);
		}

		if (wl.right_size() != 0) {
			WatchList::right_iterator it, end, j = wl.right_begin();
			Constraint::PropResult res;
			for (it = wl.right_begin(), end = wl.right_end(); it != end; ) {
				GenericWatch& w = *it++;
				res = w.propagate(*this, p);
				if (res.keepWatch) {
					*j++ = w;
				}
				if (!res.ok) {
					wl.shrink_right(std::copy(it, end, j));
					return false;
				}
			}
			wl.shrink_right(j);
		}
	}
	return DL || assign_.front == units_ || propagateUnits();
}
