game_get_can_undo (Game* self) {
	gboolean result;
	gint _tmp0_;
	g_return_val_if_fail (self != NULL, FALSE);
	_tmp0_ = self->priv->undo_index;
	result = _tmp0_ > 0;
	return result;
}
