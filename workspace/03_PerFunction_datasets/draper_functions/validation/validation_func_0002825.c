alm_blacklist_construct (GType object_type) {
	AlmBlacklist* self = NULL;
	AlmBlacklistInterface* _tmp0_ = NULL;
	AlmBlacklistInterface* _tmp1_ = NULL;
	AlmBlacklistInterface* _tmp2_ = NULL;
	AlmBlacklistInterface* _tmp3_ = NULL;
	ZeitgeistLog* _tmp4_ = NULL;
	ZeitgeistEvent* _tmp5_ = NULL;
	GError * _inner_error_ = NULL;
	self = (AlmBlacklist*) g_type_create_instance (object_type);
	_tmp1_ = g_initable_new (ALM_TYPE_BLACKLIST_INTERFACE_PROXY, NULL, &_inner_error_, "g-flags", 0, "g-name", "org.gnome.zeitgeist.Engine", "g-bus-type", G_BUS_TYPE_SESSION, "g-object-path", "/org/gnome/zeitgeist/blacklist", "g-interface-name", "org.gnome.zeitgeist.Blacklist", NULL);
	_tmp0_ = (AlmBlacklistInterface*) _tmp1_;
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return NULL;
	}
	_g_object_unref0 (self->priv->blacklist);
	self->priv->blacklist = _tmp0_;
	_tmp2_ = self->priv->blacklist;
	g_signal_connect (_tmp2_, "template-added", (GCallback) _alm_blacklist_on_template_added_alm_blacklist_interface_template_added, self);
	_tmp3_ = self->priv->blacklist;
	g_signal_connect (_tmp3_, "template-removed", (GCallback) _alm_blacklist_on_template_removed_alm_blacklist_interface_template_removed, self);
	_tmp4_ = zeitgeist_log_new ();
	_g_object_unref0 (self->priv->log);
	self->priv->log = _tmp4_;
	_tmp5_ = zeitgeist_event_new ();
	_g_object_unref0 (self->priv->incognito_event);
	self->priv->incognito_event = _tmp5_;
	return self;
}
