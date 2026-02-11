fso_gsm_plus_cpbr_issue (FsoGsmPlusCPBR* self, const gchar* cat, gint first, gint last) {
	gchar* result = NULL;
	const gchar* _tmp0_ = NULL;
	gint _tmp1_ = 0;
	gint _tmp2_ = 0;
	gchar* _tmp3_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (cat != NULL, NULL);
	_tmp0_ = cat;
	_tmp1_ = first;
	_tmp2_ = last;
	_tmp3_ = g_strdup_printf ("+CPBS=\"%s\";+CPBR=%d,%d", _tmp0_, _tmp1_, _tmp2_);
	result = _tmp3_;
	return result;
}
