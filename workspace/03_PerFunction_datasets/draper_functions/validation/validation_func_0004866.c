add(ClauseHead* h) {
	if (intTail_ < integrated_.size()) {
		ClauseHead* o = (ClauseHead*)integrated_[intTail_];
		integrated_[intTail_] = h;
		assert(o);
		if (!ctrl()->integrateUseHeuristic() || o->locked(*solver_) || o->activity().activity() > 0) {
			solver_->addLearnt(o, o->size(), Constraint_t::learnt_other);
		}
		else {
			o->destroy(solver_, true);
			solver_->stats.removeIntegrated();
		}
	}
	else {
		integrated_.push_back(h);
	}
	if (++intTail_ >= ctrl()->integrateGrace()) {
		intTail_ = 0;
	}
}
