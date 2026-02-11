prompt_next_ready (GcrSystemPrompter *self)
{
	ActivePrompt *active;
	Callback *callback;

	if (self->pv->mode == GCR_SYSTEM_PROMPTER_SINGLE &&
	    g_hash_table_size (self->pv->active) > 0)
		return;

	callback = g_queue_pop_head (&self->pv->waiting);
	if (callback == NULL)
		return;

	_gcr_debug ("preparing a prompt for callback %s@%s",
	            callback->path, callback->name);

	active = g_hash_table_lookup (self->pv->active, callback);
	g_assert (active == NULL);

	active = active_prompt_create (self, callback);
	g_return_if_fail (active != NULL);

	prompt_send_ready (active, GCR_DBUS_PROMPT_REPLY_NONE, NULL);
}
