try_explicit_object_name(const char *name)
{
	unsigned char sha1[20];
	struct ref *ref;

	if (!*name) {
		ref = alloc_ref(20);
		strcpy(ref->name, "(delete)");
		hashclr(ref->new_sha1);
		return ref;
	}
	if (get_sha1(name, sha1))
		return NULL;
	ref = alloc_ref_from_str(name);
	hashcpy(ref->new_sha1, sha1);
	return ref;
}
