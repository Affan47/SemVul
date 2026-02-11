__lambda39_ (Block1Data* _data1_, GParamSpec* pspec) {
	MathPreferencesDialog * self;
	GtkComboBox* _tmp0_ = NULL;
	MathEquation* _tmp1_ = NULL;
	gint _tmp2_ = 0;
	gint _tmp3_ = 0;
	self = _data1_->self;
	g_return_if_fail (pspec != NULL);
	_tmp0_ = self->priv->word_size_combo;
	_tmp1_ = _data1_->equation;
	_tmp2_ = math_equation_get_word_size (_tmp1_);
	_tmp3_ = _tmp2_;
	math_preferences_dialog_set_combo_box_from_int (self, _tmp0_, _tmp3_);
}
