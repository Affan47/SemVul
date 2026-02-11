text_range_valid(Filerange *r) {
	return r->start != EPOS && r->end != EPOS && r->start <= r->end;
}
