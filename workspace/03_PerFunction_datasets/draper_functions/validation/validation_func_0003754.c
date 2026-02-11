ast_party_id_merge(struct ast_party_id *base, struct ast_party_id *overlay)
{
	struct ast_party_id merged;

	merged = *base;
	if (overlay->name.valid) {
		merged.name = overlay->name;
	}
	if (overlay->number.valid) {
		merged.number = overlay->number;
	}
	if (overlay->subaddress.valid) {
		merged.subaddress = overlay->subaddress;
	}

	return merged;
}
