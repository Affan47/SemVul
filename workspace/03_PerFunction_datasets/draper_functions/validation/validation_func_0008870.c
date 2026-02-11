fso_framework_abstract_command_queue_reset (FsoFrameworkAbstractCommandQueue* self) {
	FsoFrameworkTransport* _tmp0_ = NULL;
	FsoFrameworkTransport* _tmp1_ = NULL;
	FsoFrameworkLogger* _tmp2_ = NULL;
	GeeLinkedList* _tmp3_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = fso_framework_command_queue_get_transport ((FsoFrameworkCommandQueue*) self);
	_tmp1_ = _tmp0_;
	_tmp2_ = _tmp1_->logger;
	fso_framework_logger_info (_tmp2_, "Reset commandqueue ...");
	_fso_framework_abstract_command_handler_unref0 (self->current);
	self->current = NULL;
	_tmp3_ = self->priv->q;
	gee_abstract_collection_clear ((GeeAbstractCollection*) _tmp3_);
}
