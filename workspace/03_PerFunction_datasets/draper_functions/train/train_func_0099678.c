jcnf_add_key(
	jcnf *p,
	char *key,
	jc_type type,
	unsigned char *data,
	size_t dataSize,
	char *comment
) {
	jc_error ev;
	if (p->modify == 0)
		return jc_update_nomod;
	if ((ev = jcnf_add_key_internal(p,key,type,data,dataSize,comment)) == jc_ok) {
		p->modified = 1;
	}
	return ev;
}
