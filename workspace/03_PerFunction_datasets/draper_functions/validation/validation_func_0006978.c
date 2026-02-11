request(
    GlyphIndex, const Requisition*, Requisition& result
) {
    requisition_ = result;
    Requirement& x = requisition_.x_requirement();
    if (x.defined()) {
	x.natural(x.natural() + lnatural_ + rnatural_);
	x.stretch(x.stretch() + lstretch_ + rstretch_);
	x.shrink(x.shrink() + lshrink_ + rshrink_);
    }
    Requirement& y = requisition_.y_requirement();
    if (y.defined()) {
	y.natural(y.natural() + bnatural_ + tnatural_);
	y.stretch(y.stretch() + bstretch_ + tstretch_);
	y.shrink(y.shrink() + bshrink_ + tshrink_);
    }
    result = requisition_;
}
