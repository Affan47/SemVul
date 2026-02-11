git_oid_fromstrn(git_oid *out, const char *str, size_t length)
{
	size_t p;
	int v;

	if (length < 4)
		return oid_error_invalid("input too short");

	if (length > GIT_OID_HEXSZ)
		length = GIT_OID_HEXSZ;

	for (p = 0; p < length - 1; p += 2) {
		v = (git__fromhex(str[p + 0]) << 4)
				| git__fromhex(str[p + 1]);

		if (v < 0)
			return oid_error_invalid("contains invalid characters");

		out->id[p / 2] = (unsigned char)v;
	}

	if (length % 2) {
		v = (git__fromhex(str[p + 0]) << 4);
		if (v < 0)
			return oid_error_invalid("contains invalid characters");

		out->id[p / 2] = (unsigned char)v;
		p += 2;
	}

	memset(out->id + p / 2, 0, (GIT_OID_HEXSZ - p) / 2);

	return 0;
}
