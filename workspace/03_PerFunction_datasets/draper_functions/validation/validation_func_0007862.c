target(const Event& e) const {
    EventRep& r = *e.rep();
    XEvent& xe = r.xevent_;
    if (xe.type == LeaveNotify || !r.has_pointer_location()) {
	return nil;
    }

    WindowRep& w = *rep();
    Hit hit(&e);
    w.glyph_->pick(w.canvas_, w.allocation_, 0, hit);

    Handler* h = hit.handler();
    if (h != nil &&
	(e.grabber() == nil || e.type() == Event::key || e.is_grabbing(h))
    ) {
	return h;
    }

    return nil;
}
