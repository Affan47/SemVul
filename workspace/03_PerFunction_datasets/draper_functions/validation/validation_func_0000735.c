puzzle_move_down (Puzzle* self) {
	gboolean _tmp0_;
	gboolean _tmp1_;
	g_return_if_fail (self != NULL);
	_tmp0_ = puzzle_get_can_move_down (self);
	_tmp1_ = _tmp0_;
	if (!_tmp1_) {
		return;
	}
	{
		guint _tmp2_;
		guint _tmp3_;
		gint y;
		_tmp2_ = puzzle_get_size (self);
		_tmp3_ = _tmp2_;
		y = ((gint) _tmp3_) - 2;
		{
			gboolean _tmp4_;
			_tmp4_ = TRUE;
			while (TRUE) {
				gboolean _tmp5_;
				gint _tmp7_;
				_tmp5_ = _tmp4_;
				if (!_tmp5_) {
					gint _tmp6_;
					_tmp6_ = y;
					y = _tmp6_ - 1;
				}
				_tmp4_ = FALSE;
				_tmp7_ = y;
				if (!(_tmp7_ >= 0)) {
					break;
				}
				{
					gint x;
					x = 0;
					{
						gboolean _tmp8_;
						_tmp8_ = TRUE;
						while (TRUE) {
							gboolean _tmp9_;
							gint _tmp11_;
							guint _tmp12_;
							guint _tmp13_;
							gint _tmp14_;
							gint _tmp15_;
							gint _tmp16_;
							gint _tmp17_;
							_tmp9_ = _tmp8_;
							if (!_tmp9_) {
								gint _tmp10_;
								_tmp10_ = x;
								x = _tmp10_ + 1;
							}
							_tmp8_ = FALSE;
							_tmp11_ = x;
							_tmp12_ = puzzle_get_size (self);
							_tmp13_ = _tmp12_;
							if (!(((guint) _tmp11_) < _tmp13_)) {
								break;
							}
							_tmp14_ = x;
							_tmp15_ = y;
							_tmp16_ = x;
							_tmp17_ = y;
							puzzle_switch_tiles (self, (guint) _tmp14_, (guint) _tmp15_, (guint) _tmp16_, (guint) (_tmp17_ + 1));
						}
					}
				}
			}
		}
	}
}
