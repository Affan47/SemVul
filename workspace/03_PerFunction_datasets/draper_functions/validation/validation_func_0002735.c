block1_data_unref (void * _userdata_) {
	Block1Data* _data1_;
	_data1_ = (Block1Data*) _userdata_;
#line 46 "/home/treitter/collabora/folks/tests/telepathy/individual-zeitgeist.vala"
	if (g_atomic_int_dec_and_test (&_data1_->_ref_count_)) {
#line 46 "/home/treitter/collabora/folks/tests/telepathy/individual-zeitgeist.vala"
		_g_object_unref0 (_data1_->aggregator);
#line 46 "/home/treitter/collabora/folks/tests/telepathy/individual-zeitgeist.vala"
		g_slice_free (Block1Data, _data1_);
#line 237 "individual-zeitgeist.c"
	}
}
