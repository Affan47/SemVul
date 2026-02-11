pdp_ppp_mux_real_launchPppDaemon (FsoGsmAtPdpHandler* base, gchar** cmdline, int cmdline_length1) {
	PdpPppMux * self;
	gboolean result = FALSE;
	FsoFrameworkGProcessGuard* _tmp0_ = NULL;
	FsoFrameworkGProcessGuard* _tmp1_ = NULL;
	gchar** _tmp2_ = NULL;
	gint _tmp2__length1 = 0;
	gint _tmp3_ = 0;
	gint _tmp4_ = 0;
	gboolean _tmp5_ = FALSE;
	self = (PdpPppMux*) base;
	_tmp0_ = fso_framework_gprocess_guard_new ();
	_g_object_unref0 (((FsoGsmAtPdpHandler*) self)->ppp);
	((FsoGsmAtPdpHandler*) self)->ppp = _tmp0_;
	_tmp1_ = ((FsoGsmAtPdpHandler*) self)->ppp;
	_tmp2_ = cmdline;
	_tmp2__length1 = cmdline_length1;
	_tmp5_ = fso_framework_gprocess_guard_launchWithPipes (_tmp1_, _tmp2_, _tmp2__length1, &_tmp3_, &_tmp4_);
	self->priv->inputfd = _tmp3_;
	self->priv->outputfd = _tmp4_;
	result = _tmp5_;
	return result;
}
