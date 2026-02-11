multi_term_terminal_on_window_title_changed (MultiTermTerminal* self) {
	VteTerminal* _tmp0_;
	const gchar* _tmp1_;
	const gchar* _tmp2_;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->terminal;
	_tmp1_ = vte_terminal_get_window_title (_tmp0_);
	_tmp2_ = _tmp1_;
	multi_term_terminal_set_tab_label_text (self, _tmp2_);
}
