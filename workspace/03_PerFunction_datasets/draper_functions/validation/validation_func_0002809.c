gee_concurrent_list_node_help_flagged (GeeConcurrentListNode* self, GeeConcurrentListNode* prev) {
	GeeConcurrentListNode* _tmp0_ = NULL;
	GeeConcurrentListState _tmp1_ = 0;
	GeeConcurrentListNode* _tmp2_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (prev != NULL);
	_tmp0_ = prev;
	gee_concurrent_list_node_set_backlink (self, _tmp0_);
	_tmp1_ = gee_concurrent_list_node_get_state (self);
	if (_tmp1_ != GEE_CONCURRENT_LIST_STATE_MARKED) {
		gee_concurrent_list_node_try_mark (self);
	}
	_tmp2_ = prev;
	gee_concurrent_list_node_help_marked (self, _tmp2_);
}
