gkm_transaction_real_complete (GkmTransaction *self)
{
	GList *l;

	g_return_val_if_fail (!self->completed, FALSE);
	self->completed = TRUE;
	g_object_notify (G_OBJECT (self), "completed");

	for (l = self->completes; l; l = g_list_next (l)) {
		complete_invoke (self, l->data);
		complete_destroy (l->data);
	}

	g_list_free (self->completes);
	self->completes = NULL;

	return TRUE;
}
