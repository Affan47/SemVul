parseTerm(Literal& out) {
	StreamSource& in = source_;
	term_.clear();
	int  var, last = 0;
	bool sign, sorted = true;
	unsigned hash = 0;
	do {
		match(in, '*', true);
		sign  = match(in, '~', true);
		if (!match(in, 'x', true) || !in.parseInt(var)) { ERROR("Identifier expected\n"); }
		if (var <= 0)       { ERROR("Identifier must be strictly positive\n"); }
		if (var > numVars_) { ERROR("Identifier out of bounds\n"); }
		term_.push_back(Literal(var, sign));
		sorted &= (var > last);
		hash += !sign ? hashId(static_cast<unsigned>(var)) : hashId(static_cast<unsigned>(-var));
		last = var;
		in.skipWhite();
	} while (*in == '*' || *in == '~' || *in == 'x');
	if (term_.size() == 1) {
		out = term_[0];
	}
	else {
		assert(nlc_);
		if (!sorted) {
			std::sort(term_.begin(), term_.end());
			LitVec::size_type j  = 1;
			LitVec::size_type i  = 0;
			LitVec::size_type end= term_.size();
			while (j != end) {
				if (term_[i].var() != term_[j].var()) {
					term_[++i] = term_[j++];
				}
				else if (term_[i] == term_[j]) {
					++j;
				}
				else {
					out = negLit(0);
					return;
				}
			}
			shrinkVecTo(term_, ++i);
		}
		if (!nlc_->getProduct(term_, hash, out)) {
			out = posLit(++nextVar_);
			assert(ctx_.validVar(out.var()));
			nlc_->addProduct(term_, hash, out);
		}
	}
}
