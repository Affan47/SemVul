update_top() {
  if (!top_) top_ = item_first();
  if (position_ != real_position_) {
    void* l;
    int ly;
    int yy = position_;

    if (!top_ || yy <= (real_position_/2)) {
      l = item_first();
      ly = 0;
    } else {
      l = top_;
      ly = real_position_-offset_;
    }
    if (!l) {
      top_ = 0;
      offset_ = 0;
      real_position_ = 0;
    } else {
      int hh = item_quick_height(l);

      while (ly > yy) {
	void* l1 = item_prev(l);
	if (!l1) {ly = 0; break;}
	l  = l1;
	hh = item_quick_height(l);
	ly -= hh;
      }
      while ((ly+hh) <= yy) {
	void* l1 = item_next(l);
	if (!l1) {yy = ly+hh-1; break;}
	l = l1;
	ly += hh;
	hh = item_quick_height(l);
      }

      for (;;) {
	hh = item_height(l);
	if ((ly+hh) > yy) break;

	void* l1 = item_prev(l);
	if (!l1) {ly = yy = 0; break;}
	l = l1; yy = position_ = ly = ly-item_quick_height(l);
      }

      top_ = l;
      offset_ = yy-ly;
      real_position_ = yy;
    }
    damage(FL_DAMAGE_SCROLL);
  }
}
