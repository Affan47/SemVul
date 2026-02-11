PosInt2D_SetFraction(GF_Node *node, GF_Route *route)
{
	M_PositionInterpolator2D *_this = (M_PositionInterpolator2D *)node;
	u32 i;
	Fixed frac;

	if (! _this->key.count) return;
	if (_this->keyValue.count != _this->key.count) return;


	if (_this->set_fraction < _this->key.vals[0]) {
		_this->value_changed = _this->keyValue.vals[0];
	} else if (_this->set_fraction >= _this->key.vals[_this->key.count-1]) {
		_this->value_changed = _this->keyValue.vals[_this->keyValue.count-1];
	} else {
		for (i=1; i<_this->key.count; i++) {

			if (_this->set_fraction < _this->key.vals[i-1]) continue;
			if (_this->set_fraction >= _this->key.vals[i]) continue;

			frac = GetInterpolateFraction(_this->key.vals[i-1], _this->key.vals[i], _this->set_fraction);
			_this->value_changed.x = Interpolate(_this->keyValue.vals[i-1].x, _this->keyValue.vals[i].x, frac);
			_this->value_changed.y = Interpolate(_this->keyValue.vals[i-1].y, _this->keyValue.vals[i].y, frac);
			break;
		}
	}
	gf_node_event_out(node, 3);
}
