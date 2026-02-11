reduceSort(uint32 maxR, const CmpScore& sc) {
	typedef PodVector<CmpScore::ViewPair>::type HeapType;
	maxR              = std::min(maxR, (uint32)learnts_.size());
	const uint32 glue = sc.glue;
	DBInfo       res  = {0,0,0};
	HeapType     heap;
	heap.reserve(maxR);
	bool isGlue, isLocked;
	for (LitVec::size_type i = 0; i != learnts_.size(); ++i) {
		LearntConstraint* c = static_cast<LearntConstraint*>(learnts_[i]);
		CmpScore::ViewPair vp(i, c->activity());
		res.pinned += (isGlue   = vp.second.lbd() <= glue);
		res.locked += (isLocked = c->locked(*this));
		if (!isLocked && !isGlue) {
			if (maxR) {
				heap.push_back(vp);
				if (--maxR == 0) { std::make_heap(heap.begin(), heap.end(), sc); }
			}
			else if (sc(vp, heap[0])) {
				std::pop_heap(heap.begin(), heap.end(), sc);
				heap.back() = vp;
				std::push_heap(heap.begin(), heap.end(), sc);
			}
		}
	}

	for (HeapType::const_iterator it = heap.begin(), end = heap.end(); it != end; ++it) {
		learnts_[it->first]->destroy(this, true);
		learnts_[it->first] = 0;
	}

	uint32 j = 0;
	for (LitVec::size_type i = 0; i != learnts_.size(); ++i) {
		if (LearntConstraint* c = static_cast<LearntConstraint*>(learnts_[i])) {
			c->decreaseActivity();
			learnts_[j++] = c;
		}
	}
	res.size = j;
	return res;
}
