update_style_info() {
    Style* s = style_;
    Session* session = Session::instance();
    Display* d = session->default_display();
    String v;
    if (s->find_attribute("font", v) || s->find_attribute("Font", v)) {
	const Font* f = Font::lookup(v);
	if (f == nil) {
	    if (font_ == nil) {
		const char* default_font = "fixed";
		report_error(session, "open font", v, default_font);
		font_ = Font::lookup(default_font);
		Resource::ref(font_);
	    }
	} else {
	    Resource::ref(f);
	    Resource::unref(font_);
	    font_ = f;
	}
    }
    if (s->find_attribute("foreground", v) ||
	s->find_attribute("Foreground", v)
    ) {
	const Color* c = Color::lookup(d, v);
	if (c == nil) {
	    if (foreground_ == nil) {
		const char* default_foreground = "#000000";
		report_error(session, "find color", v, default_foreground);
		foreground_ = Color::lookup(d, default_foreground);
		Resource::ref(foreground_);
	    }
	} else {
	    Resource::ref(c);
	    Resource::unref(foreground_);
	    foreground_ = c;
	}
    }
    if (s->find_attribute("background", v) ||
	s->find_attribute("Background", v)
    ) {
	const Color* c = Color::lookup(d, v);
	if (c == nil) {
	    if (background_ == nil) {
		const char* default_background = "#ffffff";
		report_error(session, "find color", v, default_background);
		background_ = Color::lookup(d, default_background);
		Resource::ref(background_);
	    }
	} else {
	    Resource::ref(c);
	    Resource::unref(background_);
	    background_ = c;
	}
    }
    style_changed_ = false;
}
