hfsplus_hash_dentry(const struct dentry *dentry, struct qstr *str)
{
	struct super_block *sb = dentry->d_sb;
	const char *astr;
	const u16 *dstr;
	int casefold, decompose, size, len;
	unsigned long hash;
	wchar_t c;
	u16 c2;

	casefold = test_bit(HFSPLUS_SB_CASEFOLD, &HFSPLUS_SB(sb)->flags);
	decompose = !test_bit(HFSPLUS_SB_NODECOMPOSE, &HFSPLUS_SB(sb)->flags);
	hash = init_name_hash();
	astr = str->name;
	len = str->len;
	while (len > 0) {
		int uninitialized_var(dsize);
		size = asc2unichar(sb, astr, len, &c);
		astr += size;
		len -= size;

		if (decompose)
			dstr = decompose_unichar(c, &dsize);
		else
			dstr = NULL;
		if (dstr) {
			do {
				c2 = *dstr++;
				if (casefold)
					c2 = case_fold(c2);
				if (!casefold || c2)
					hash = partial_name_hash(c2, hash);
			} while (--dsize > 0);
		} else {
			c2 = c;
			if (casefold)
				c2 = case_fold(c2);
			if (!casefold || c2)
				hash = partial_name_hash(c2, hash);
		}
	}
	str->hash = end_name_hash(hash);

	return 0;
}
