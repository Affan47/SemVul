structure_is_section (StructType type) {
	gboolean result = FALSE;
	gboolean _tmp0_ = FALSE;
	StructType _tmp1_ = 0;
	_tmp1_ = type;
	if (STRUCT_TYPE_PART <= _tmp1_) {
		StructType _tmp2_ = 0;
		_tmp2_ = type;
		_tmp0_ = _tmp2_ <= STRUCT_TYPE_SUBPARAGRAPH;
	} else {
		_tmp0_ = FALSE;
	}
	result = _tmp0_;
	return result;
}
