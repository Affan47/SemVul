_persona_store_tests_set_up_persona_store (PersonaStoreTests* self, FolksPersonaStore* store) {
	Block2Data* _data2_;
	FolksPersonaStore* _tmp0_ = NULL;
	FolksPersonaStore* _tmp1_ = NULL;
	FolksPersonaStore* _tmp2_ = NULL;
#line 106 "/home/treitter/collabora/folks/tests/eds/persona-store-tests.vala"
	g_return_if_fail (self != NULL);
#line 106 "/home/treitter/collabora/folks/tests/eds/persona-store-tests.vala"
	g_return_if_fail (store != NULL);
#line 106 "/home/treitter/collabora/folks/tests/eds/persona-store-tests.vala"
	_data2_ = g_slice_new0 (Block2Data);
#line 106 "/home/treitter/collabora/folks/tests/eds/persona-store-tests.vala"
	_data2_->_ref_count_ = 1;
#line 106 "/home/treitter/collabora/folks/tests/eds/persona-store-tests.vala"
	_data2_->self = g_object_ref (self);
#line 106 "/home/treitter/collabora/folks/tests/eds/persona-store-tests.vala"
	_tmp0_ = store;
#line 106 "/home/treitter/collabora/folks/tests/eds/persona-store-tests.vala"
	_tmp1_ = _g_object_ref0 (_tmp0_);
#line 106 "/home/treitter/collabora/folks/tests/eds/persona-store-tests.vala"
	_g_object_unref0 (_data2_->store);
#line 106 "/home/treitter/collabora/folks/tests/eds/persona-store-tests.vala"
	_data2_->store = _tmp1_;
#line 108 "/home/treitter/collabora/folks/tests/eds/persona-store-tests.vala"
	_tmp2_ = _data2_->store;
#line 108 "/home/treitter/collabora/folks/tests/eds/persona-store-tests.vala"
	folks_persona_store_prepare (_tmp2_, ___lambda5__gasync_ready_callback, block2_data_ref (_data2_));
#line 106 "/home/treitter/collabora/folks/tests/eds/persona-store-tests.vala"
	block2_data_unref (_data2_);
#line 106 "/home/treitter/collabora/folks/tests/eds/persona-store-tests.vala"
	_data2_ = NULL;
#line 901 "persona-store-tests.c"
}
