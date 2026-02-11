assign(const ParsedValues& p) {
	if (!p.ctx) return false;
	struct Assign {
		Assign(ParsedOptions* x) : self(x) {}
		void assign(const ParsedValues& p) {
			begin = it = p.begin();

			std::string ctx = p.ctx ? p.ctx->caption() : "";
			for (ParsedValues::iterator end = p.end(); it != end; ++it) {
				const Option& o = *it->first;
				if (int ret = self->assign(o, it->second)) {
					throw ValueError(ctx, static_cast<ValueError::Type>(ret-1), o.name(), it->second);
				}
			}
		}
		~Assign() {
			for (ParsedValues::iterator x = begin, end = this->it; x != end; ++x) {
				const Option& o = *x->first;
				assert(o.value()->state() == Value::value_fixed || self->parsed_.count(o.name()) != 0);
				if (o.value()->state() == Value::value_fixed) {
					self->parsed_.insert(x->first->name());
					o.value()->state(Value::value_unassigned);
				}
			}
		}
		ParsedOptions* self;
		ParsedValues::iterator begin;
		ParsedValues::iterator it;
	} scoped(this);
	scoped.assign(p);
	return true;
}
