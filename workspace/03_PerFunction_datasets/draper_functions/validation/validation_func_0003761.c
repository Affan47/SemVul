befs_nls2utf(struct super_block *sb, const char *in,
	     int in_len, char **out, int *out_len)
{
	struct nls_table *nls = BEFS_SB(sb)->nls;
	int i, o;
	wchar_t uni;
	int unilen, utflen;
	char *result;


	int maxlen = (3 * in_len) + 1;

	befs_debug(sb, "---> %s\n", __func__);

	if (!nls) {
		befs_error(sb, "%s called with no NLS table loaded.",
			   __func__);
		return -EINVAL;
	}

	*out = result = kmalloc(maxlen, GFP_NOFS);
	if (!*out) {
		befs_error(sb, "%s cannot allocate memory", __func__);
		*out_len = 0;
		return -ENOMEM;
	}

	for (i = o = 0; i < in_len; i += unilen, o += utflen) {


		unilen = nls->char2uni(&in[i], in_len - i, &uni);
		if (unilen < 0)
			goto conv_err;


		utflen = utf32_to_utf8(uni, &result[o], 3);
		if (utflen <= 0)
			goto conv_err;
	}

	result[o] = '\0';
	*out_len = o;

	befs_debug(sb, "<--- %s", __func__);

	return i;

      conv_err:
	befs_error(sb, "Name using charecter set %s contains a charecter that "
		   "cannot be converted to unicode.", nls->charset);
	befs_debug(sb, "<--- %s", __func__);
	kfree(result);
	return -EILSEQ;
}
