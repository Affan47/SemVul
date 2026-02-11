hit_thumb(Slider* s, const Event& event) {
    Coord x = event.pointer_x();
    Coord y = event.pointer_y();
    const Extension& e = thumb_patch_->extension();
    if (x >= e.left() && x < e.right() && y >= e.bottom() && y < e.top()) {
	Canvas* c = s->canvas();
	const Transformer& t = s->transformer();
	Hit hit(&event);
	hit.transform(t);
	c->push_transform();
	c->transformer(t);
	thumb_patch_->pick(c, thumb_patch_->allocation(), 0, hit);
	c->pop_transform();
	return hit.any() ? 0 : 1;
    }
    if (x < e.left() || y < e.bottom()) {
	return -1;
    }
    return 1;
}
