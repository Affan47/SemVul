major_alloc_small_pinned_obj (MonoVTable *vtable, size_t size, gboolean has_references)
{
	void *res;

	res = alloc_obj (vtable, size, TRUE, has_references);


	 if (!res) {
		sgen_perform_collection (0, GENERATION_OLD, "pinned alloc failure", TRUE);
		res = alloc_obj (vtable, size, TRUE, has_references);
	 }
	 return res;
}
