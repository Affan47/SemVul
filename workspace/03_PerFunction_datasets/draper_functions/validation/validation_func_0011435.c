ccResolve(LitVec& cc, uint32 pos, const LitVec& reason) {
	heuristic_->updateReason(*this, reason, cc[pos]);
	Literal x;
	for (LitVec::size_type i = 0; i != reason.size(); ++i) {
		x = reason[i];
		assert(isTrue(x));
		if (!seen(x.var())) {
			markLevel(level(x.var()));
			cc.push_back(~x);
		}
	}
	clearSeen(cc[pos].var());
	unmarkLevel(level(cc[pos].var()));
	cc[pos] = cc.back();
	cc.pop_back();
}
