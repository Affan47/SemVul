ccss_grammar_destroy (ccss_grammar_t *self)
{
	g_assert (self && self->reference_count > 0);

	self->reference_count--;

	if (0 == self->reference_count) {
		g_hash_table_destroy (self->properties), self->properties = NULL;
		g_hash_table_destroy (self->functions), self->functions = NULL;
		g_free (self);
	}
}
