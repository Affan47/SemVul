void delete_encoder_persistent(void *encode)
{
	encodePtr t = *((encodePtr*)encode);
	if (t->details.ns) {
		free(t->details.ns);
	}
	if (t->details.type_str) {
		free(t->details.type_str);
	}

	assert(t->details.map == NULL);
	free(t);
}
