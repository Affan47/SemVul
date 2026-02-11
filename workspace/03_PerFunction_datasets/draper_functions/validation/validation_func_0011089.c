allocate(Canvas* c, const Allocation& allocation, Extension& ext) {
    canvas_ = c;
    allocation_ = allocation;
    if (background_ != nil) {
        background_->allocate(c, allocation, ext);
    }
    GlyphIndex count = info_->count();
    for (GlyphIndex index = 0; index < count; ++index) {
        PageInfo& info = info_->item_ref(index);
        if (info.glyph_ != nil) {
            Allocation& a = info.allocation_;
            Extension& b = info.extension_;
            Requisition s;
            info.glyph_->request(s);
            Allotment ax = Allotment(
                allocation.x() + info.x_,
                s.requirement(Dimension_X).natural(),
                s.requirement(Dimension_X).alignment()
            );
            Allotment ay = Allotment(
                allocation.y() + info.y_,
                s.requirement(Dimension_Y).natural(),
                s.requirement(Dimension_Y).alignment()
            );
            if (
                !(info.status_ & PageInfoAllocated)
                || !ax.equals(a.allotment(Dimension_X), epsilon)
                || !ay.equals(a.allotment(Dimension_Y), epsilon)
            ) {
                if (c != nil && (info.status_ & PageInfoExtended)) {
                    c->damage(b);
                }
                a.allot(Dimension_X, ax);
                a.allot(Dimension_Y, ay);
		b.clear();
                info.glyph_->allocate(c, a, b);
                if (c != nil) {
                    c->damage(b);
                }
            }
            info.status_ |= PageInfoAllocated|PageInfoExtended;
            ext.merge(b);
        }
    }
}
