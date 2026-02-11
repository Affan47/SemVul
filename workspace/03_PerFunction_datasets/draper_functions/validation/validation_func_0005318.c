math_variables_get (MathVariables* self, const gchar* name) {
	Number* result = NULL;
	GHashTable* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	gconstpointer _tmp2_ = NULL;
	Number* _tmp3_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (name != NULL, NULL);
	_tmp0_ = self->priv->registers;
	_tmp1_ = name;
	_tmp2_ = g_hash_table_lookup (_tmp0_, _tmp1_);
	_tmp3_ = _number_ref0 ((Number*) _tmp2_);
	result = _tmp3_;
	return result;
}
