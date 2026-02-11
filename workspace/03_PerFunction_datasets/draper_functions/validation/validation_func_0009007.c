set_group_leader(ManagedWindowHintInfo& info) {
    if (group_leader_ == nil) {
	info.hints_->flags &= ~WindowGroupHint;
	info.hints_->window_group = None;
	return true;
    } else {
	XWindow g = group_leader_->rep()->xwindow_;
	if (g != WindowRep::unbound) {
	    info.hints_->flags |= WindowGroupHint;
	    info.hints_->window_group = g;
	    return true;
	}
    }
    return false;
}
